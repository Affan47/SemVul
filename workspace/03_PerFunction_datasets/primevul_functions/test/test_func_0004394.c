GF_Err GetMediaTime(GF_TrackBox *trak, Bool force_non_empty, u64 movieTime, u64 *MediaTime, s64 *SegmentStartTime, s64 *MediaOffset, u8 *useEdit, u64 *next_edit_start_plus_one)
{
#if 0
	GF_Err e;
	u32 sampleNumber, prevSampleNumber;
	u64 firstDTS;
#endif
	u32 i, count;
	Bool last_is_empty = 0;
	u64 time, lastSampleTime;
	s64 mtime;
	GF_EdtsEntry *ent;
	Double scale_ts;
	GF_SampleTableBox *stbl = trak->Media->information->sampleTable;

	if (next_edit_start_plus_one) *next_edit_start_plus_one = 0;
	*useEdit = 1;
	*MediaTime = 0;

	*SegmentStartTime = -1;
	*MediaOffset = -1;
	if (!trak->moov->mvhd->timeScale || !trak->Media->mediaHeader->timeScale || !stbl->SampleSize) {
		return GF_ISOM_INVALID_FILE;
	}


	if (!stbl->SampleSize->sampleCount) {
		lastSampleTime = 0;
	} else {
		lastSampleTime = trak->Media->mediaHeader->duration;
	}


	if (! trak->editBox || !trak->editBox->editList) {
		*MediaTime = movieTime;

		if ((*MediaTime > lastSampleTime)
#ifndef GPAC_DISABLE_ISOM_FRAGMENTS
		        && !trak->moov->mov->moof
#endif
		   ) {
			*MediaTime = lastSampleTime;
		}
		*useEdit = 0;
		return GF_OK;
	}

	scale_ts = trak->Media->mediaHeader->timeScale;
	scale_ts /= trak->moov->mvhd->timeScale;

	time = 0;
	ent = NULL;
	count=gf_list_count(trak->editBox->editList->entryList);
	for (i=0; i<count; i++) {
		ent = (GF_EdtsEntry *)gf_list_get(trak->editBox->editList->entryList, i);
		if ( (time + ent->segmentDuration) * scale_ts > movieTime) {
			if (!force_non_empty || (ent->mediaTime >= 0)) {
				if (next_edit_start_plus_one) *next_edit_start_plus_one = 1 + (u64) ((time + ent->segmentDuration) * scale_ts);
				goto ent_found;
			}
		}
		time += ent->segmentDuration;
		last_is_empty = ent->segmentDuration ? 0 : 1;
	}

	if (last_is_empty) {
		ent = (GF_EdtsEntry *)gf_list_last(trak->editBox->editList->entryList);
		if (ent->mediaRate == 0x10000) {
			*MediaTime = movieTime + ent->mediaTime;
		} else {
			ent = (GF_EdtsEntry *)gf_list_get(trak->editBox->editList->entryList, 0);
			if (ent->mediaRate == -0x10000) {
				u64 dur = (u64) (ent->segmentDuration * scale_ts);
				*MediaTime = (movieTime > dur) ? (movieTime-dur) : 0;
			}
		}
		*useEdit = 0;
		return GF_OK;
	}


	if (!ent) {
		*MediaTime = movieTime;

		if (*MediaTime > lastSampleTime) *MediaTime = lastSampleTime;
		*useEdit = 0;
		return GF_OK;
	}

	*MediaTime = lastSampleTime;
	return GF_OK;

ent_found:

	*SegmentStartTime = time;


	if (ent->mediaTime < 0) {
		*MediaTime = 0;
		return GF_OK;
	}

	if (! ent->mediaRate) {
		*MediaTime = ent->mediaTime;

		*MediaOffset = 0;
		*useEdit = 2;
		return GF_OK;
	}


	mtime = ent->mediaTime + movieTime - (time * trak->Media->mediaHeader->timeScale / trak->moov->mvhd->timeScale);
	if (mtime<0) mtime = 0;
	*MediaTime = (u64) mtime;
	*MediaOffset = ent->mediaTime;

#if 0


	e = stbl_findEntryForTime(stbl, (u32) *MediaTime, 1, &sampleNumber, &prevSampleNumber);
	if (e) return e;


	if (!sampleNumber && !prevSampleNumber) {
		*MediaTime = lastSampleTime;
		return GF_OK;
	}

	if (!sampleNumber) sampleNumber = prevSampleNumber;

	stbl_GetSampleDTS(stbl->TimeToSample, sampleNumber, &DTS);
	CTS = 0;
	if (stbl->CompositionOffset) stbl_GetSampleCTS(stbl->CompositionOffset, sampleNumber, &CTS);


	e = stbl_findEntryForTime(stbl, (u32) ent->mediaTime, 0, &sampleNumber, &prevSampleNumber);
	if (e) return e;


	if (!sampleNumber && !prevSampleNumber) {
		*MediaTime = lastSampleTime;
		return GF_ISOM_INVALID_FILE;
	}
	if (!sampleNumber) sampleNumber = prevSampleNumber;

	stbl_GetSampleDTS(stbl->TimeToSample, sampleNumber, &firstDTS);


	*MediaOffset = firstDTS;
#endif
	return GF_OK;
}
