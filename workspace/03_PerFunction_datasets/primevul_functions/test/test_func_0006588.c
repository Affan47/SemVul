GF_Err DoInterleave(MovieWriter *mw, GF_List *writers, GF_BitStream *bs, u8 Emulation, u64 StartOffset, Bool drift_inter)
{
	u32 i, tracksDone;
	TrackWriter *tmp, *curWriter;
	GF_Err e;
	u32 descIndex, sampSize, chunkNumber;
	u64 DTS;
	u32 moov_timescale;
	u16 curGroupID;
	Bool forceNewChunk, writeGroup;
	GF_StscEntry *stsc_ent;

	u64 offset, sampOffset, size, mdatSize;
	u32 count;
	GF_ISOFile *movie = mw->movie;

	mdatSize = 0;

#ifdef TEST_LARGE_FILES
	if (!Emulation) {
		char *blank;
		u32 count, i;
		i = count = 0;
		blank = gf_malloc(sizeof(char)*1024*1024);
		memset(blank, 0, sizeof(char)*1024*1024);
		count = 4096;
		memset(blank, 0, sizeof(char)*1024*1024);
		while (i<count) {
			u32 res = gf_bs_write_data(bs, blank, 1024*1024);
			if (res != 1024*1024) {
				GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("error writing to disk: only %d bytes written\n", res));
			}
			i++;
			GF_LOG(GF_LOG_ERROR, GF_LOG_CORE, ("writing blank block: %.02f done - %d/%d \r", (100.0*i)/count , i, count));
		}
		gf_free(blank);
	}
	mdatSize = 4096*1024;
	mdatSize *= 1024;
#endif


	if (movie->meta) {
		e = DoWriteMeta(movie, movie->meta, bs, Emulation, StartOffset, &size);
		if (e) return e;
		mdatSize += size;
		StartOffset += (u32) size;
	}
	if (movie->moov) {
		if (movie->moov->meta) {
			e = DoWriteMeta(movie, movie->moov->meta, bs, Emulation, StartOffset, &size);
			if (e) return e;
			mdatSize += size;
			StartOffset += (u32) size;
		}
		i=0;
		while ((tmp = (TrackWriter*)gf_list_enum(writers, &i))) {
			if (tmp->mdia->mediaTrack->meta) {
				e = DoWriteMeta(movie, tmp->mdia->mediaTrack->meta, bs, Emulation, StartOffset, &size);
				if (e) return e;
				mdatSize += size;
				StartOffset += (u32) size;
			}
		}
	}


	if (movie->storageMode == GF_ISOM_STORE_TIGHT)
		return DoFullInterleave(mw, writers, bs, Emulation, StartOffset);

	curGroupID = 1;

	offset = StartOffset;
	tracksDone = 0;

#ifdef TEST_LARGE_FILES
	offset += mdatSize;
#endif

	moov_timescale = movie->moov && movie->moov->mvhd ? movie->moov->mvhd->timeScale : 1000;

	count = gf_list_count(writers);

	while (1) {

		u64 chunkLastDTS = 0;

		u32 chunkLastScale = 0;

		writeGroup = 1;


		while (writeGroup) {
			curWriter = NULL;
			for (i=0 ; i < count; i++) {
				tmp = (TrackWriter*)gf_list_get(writers, i);


				if (tmp->isDone) continue;


				if (tmp->stbl->groupID != curGroupID) continue;


				while (1) {
					Bool self_contained;
					u32 nb_samp = 1;
					u32 sample_dur;
					u64 chunk_prev_dur;

					if (tmp->sampleNumber > tmp->stbl->SampleSize->sampleCount) {
						tmp->isDone = 1;
						tracksDone ++;
						break;
					}


					stbl_GetSampleDTS_and_Duration(tmp->stbl->TimeToSample, tmp->sampleNumber, &DTS, &sample_dur);


					if ( ( (DTS - tmp->DTSprev) + tmp->chunkDur) * moov_timescale > movie->interleavingTime * tmp->timeScale

					        || (drift_inter && chunkLastDTS && ( ((u64)tmp->DTSprev*chunkLastScale) > ((u64)chunkLastDTS*tmp->timeScale)) )
					   ) {

						if (!tmp->chunkDur) {
							forceNewChunk = 1;
						} else {

							tmp->chunkDur = 0;

							break;
						}
					} else {
						forceNewChunk = tmp->chunkDur ? 0 : 1;
					}

					curWriter = tmp;


					if (tmp->sampleNumber == 2 && !tmp->chunkDur && gf_sys_old_arch_compat() ) {
						forceNewChunk = 0;
					}

					chunk_prev_dur = tmp->chunkDur;


					if (!gf_sys_old_arch_compat()) {
						tmp->chunkDur += sample_dur;
					} else {

						tmp->chunkDur += (u32) (DTS - tmp->DTSprev);
					}
					tmp->DTSprev = DTS;

					e = stbl_GetSampleInfos(curWriter->stbl, curWriter->sampleNumber, &sampOffset, &chunkNumber, &descIndex, &stsc_ent);
					if (e)
						return e;
					e = stbl_GetSampleSize(curWriter->stbl->SampleSize, curWriter->sampleNumber, &sampSize);
					if (e)
						return e;

					self_contained = ((curWriter->all_dref_mode==ISOM_DREF_SELF) || Media_IsSelfContained(curWriter->mdia, descIndex)) ? GF_TRUE : GF_FALSE;

					update_writer_constant_dur(movie, curWriter, stsc_ent, &nb_samp, &sampSize, GF_FALSE);

					if (curWriter->stbl->MaxChunkSize && (curWriter->chunkSize + sampSize > curWriter->stbl->MaxChunkSize)) {
						curWriter->chunkSize = 0;
						tmp->chunkDur -= chunk_prev_dur;
						forceNewChunk = 1;
					}
					curWriter->chunkSize += sampSize;


					if (Emulation) {

						if (self_contained) {
							e = stbl_SetChunkAndOffset(curWriter->stbl, curWriter->sampleNumber, descIndex, curWriter->stsc, &curWriter->stco, offset, forceNewChunk, nb_samp);
							if (e)
								return e;
							offset += sampSize;
							mdatSize += sampSize;
						} else {
							if (curWriter->prev_offset != sampOffset) forceNewChunk = 1;
							curWriter->prev_offset = sampOffset + sampSize;


							e = stbl_SetChunkAndOffset(curWriter->stbl, curWriter->sampleNumber, descIndex, curWriter->stsc, &curWriter->stco, sampOffset, forceNewChunk, nb_samp);
							if (e) return e;
						}
					} else {

						if (self_contained) {
							e = WriteSample(mw, sampSize, sampOffset, stsc_ent->isEdited, bs, nb_samp);
							if (e)
								return e;
						}
					}

					if (curWriter->sampleNumber >= curWriter->stbl->SampleSize->sampleCount) {
						curWriter->isDone = 1;

						tracksDone ++;
						break;
					} else {
						curWriter->sampleNumber += nb_samp;
					}
				}

				if (drift_inter && curWriter) {
					chunkLastScale = curWriter->timeScale;
					chunkLastDTS = curWriter->DTSprev;


					chunkLastDTS += curWriter->timeScale * movie->interleavingTime / moov_timescale;
				}
			}

			if (!curWriter) {
				writeGroup = 0;
				continue;
			}
		}

		if (tracksDone == gf_list_count(writers)) break;

		curGroupID ++;
	}
	if (movie->mdat) movie->mdat->dataSize = mdatSize;
	return GF_OK;
}
