GF_Err DoFullInterleave(MovieWriter *mw, GF_List *writers, GF_BitStream *bs, u8 Emulation, u64 StartOffset)
{

	u32 i, tracksDone;
	TrackWriter *tmp, *curWriter, *prevWriter;
	GF_Err e;
	u64 DTS, DTStmp, TStmp;
	s64 res;
	u32 descIndex, sampSize, chunkNumber;
	u16 curGroupID, curTrackPriority;
	Bool forceNewChunk, writeGroup;
	GF_StscEntry *stsc_ent;

	u64 offset, totSize, sampOffset;
	GF_ISOFile *movie = mw->movie;

	totSize = 0;
	curGroupID = 1;

	prevWriter = NULL;

	offset = StartOffset;
	tracksDone = 0;


	while (1) {
		writeGroup = 1;


		while (writeGroup) {
			u32 nb_samp = 1;
			Bool self_contained, chunked_forced=GF_FALSE;

			curWriter = NULL;
			DTStmp = (u64) -1;
			TStmp = 0;
			curTrackPriority = (u16) -1;

			i=0;
			while ((tmp = (TrackWriter*)gf_list_enum(writers, &i))) {


				if (tmp->isDone || tmp->stbl->groupID != curGroupID) continue;


				stbl_GetSampleDTS(tmp->stbl->TimeToSample, tmp->sampleNumber, &DTS);
				res = TStmp ? DTStmp * tmp->timeScale - DTS * TStmp : 0;
				if (res < 0) continue;
				if ((!res) && curTrackPriority <= tmp->stbl->trackPriority) continue;
				curWriter = tmp;
				curTrackPriority = tmp->stbl->trackPriority;
				DTStmp = DTS;
				TStmp = tmp->timeScale;
			}

			if (!curWriter) {

				writeGroup = 0;
				continue;
			}

			if (curWriter->sampleNumber > curWriter->stbl->SampleSize->sampleCount) {
				curWriter->isDone = 1;
				tracksDone ++;
				continue;
			}

			e = stbl_GetSampleInfos(curWriter->stbl, curWriter->sampleNumber, &sampOffset, &chunkNumber, &descIndex, &stsc_ent);
			if (e) return e;
			e = stbl_GetSampleSize(curWriter->stbl->SampleSize, curWriter->sampleNumber, &sampSize);
			if (e) return e;

			update_writer_constant_dur(movie, curWriter, stsc_ent, &nb_samp, &sampSize, GF_FALSE);

			if (curWriter->stbl->MaxChunkSize && (curWriter->chunkSize + sampSize > curWriter->stbl->MaxChunkSize)) {
				curWriter->chunkSize = 0;
				chunked_forced = forceNewChunk = 1;
			}
			curWriter->chunkSize += sampSize;

			self_contained = ((curWriter->all_dref_mode==ISOM_DREF_SELF) || Media_IsSelfContained(curWriter->mdia, descIndex) ) ? GF_TRUE : GF_FALSE;


			if (Emulation) {

				if (!chunked_forced) {
					if (curWriter != prevWriter) {
						forceNewChunk = 1;
					} else {
						forceNewChunk = 0;
					}
				}

				if (self_contained) {
					e = stbl_SetChunkAndOffset(curWriter->stbl, curWriter->sampleNumber, descIndex, curWriter->stsc, &curWriter->stco, offset, forceNewChunk, nb_samp);
					if (e) return e;
					offset += sampSize;
					totSize += sampSize;
				} else {

					curWriter->prev_offset = sampOffset + sampSize;


					e = stbl_SetChunkAndOffset(curWriter->stbl, curWriter->sampleNumber, descIndex, curWriter->stsc, &curWriter->stco, sampOffset, chunked_forced, nb_samp);
					if (e) return e;
				}
			} else {

				if (self_contained) {
					e = WriteSample(mw, sampSize, sampOffset, stsc_ent->isEdited, bs, 1);
					if (e) return e;
				}
			}

			if (curWriter->sampleNumber == curWriter->stbl->SampleSize->sampleCount) {
				curWriter->isDone = 1;

				tracksDone ++;
			} else {
				curWriter->sampleNumber += nb_samp;
			}
			prevWriter = curWriter;
		}

		if (tracksDone == gf_list_count(writers)) break;

		curGroupID ++;
	}
	if (movie->mdat)
		movie->mdat->dataSize = totSize;
	return GF_OK;
}
