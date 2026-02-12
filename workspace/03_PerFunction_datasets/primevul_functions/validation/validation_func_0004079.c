GF_Err gf_isom_get_sample_for_movie_time(GF_ISOFile *the_file, u32 trackNumber, u64 movieTime, u32 *StreamDescriptionIndex, GF_ISOSearchMode SearchMode, GF_ISOSample **sample, u32 *sampleNumber, u64 *data_offset)
{
	Double tsscale;
	GF_Err e;
	GF_TrackBox *trak;
	u64 mediaTime, nextMediaTime;
	s64 segStartTime, mediaOffset;
	u32 sampNum;
	u8 useEdit;

	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak) return GF_BAD_PARAM;


	if (trak->Header->initial_duration
		&& (movieTime * trak->moov->mvhd->timeScale > trak->Header->initial_duration * trak->Media->mediaHeader->timeScale)
	) {
		if (sampleNumber) *sampleNumber = 0;
		*StreamDescriptionIndex = 0;
		return GF_EOS;
	}


	mediaTime = segStartTime = 0;
	*StreamDescriptionIndex = 0;
	nextMediaTime = 0;

	e = GetMediaTime(trak, (SearchMode==GF_ISOM_SEARCH_SYNC_FORWARD) ? GF_TRUE : GF_FALSE, movieTime, &mediaTime, &segStartTime, &mediaOffset, &useEdit, &nextMediaTime);
	if (e) return e;


	if (useEdit && mediaOffset == -1) {
		if ((SearchMode==GF_ISOM_SEARCH_FORWARD) || (SearchMode==GF_ISOM_SEARCH_BACKWARD)) {

			if (SearchMode==GF_ISOM_SEARCH_FORWARD)
				e = GetNextMediaTime(trak, movieTime, &mediaTime);
			else
				e = GetPrevMediaTime(trak, movieTime, &mediaTime);
			if (e) return e;
			return gf_isom_get_sample_for_movie_time(the_file, trackNumber, (u32) mediaTime, StreamDescriptionIndex, GF_ISOM_SEARCH_SYNC_FORWARD, sample, sampleNumber, data_offset);
		}
		if (sampleNumber) *sampleNumber = 0;
		if (sample) {
			if (! (*sample)) {
				*sample = gf_isom_sample_new();
				if (! *sample) return GF_OUT_OF_MEM;
			}
			(*sample)->DTS = movieTime;
			(*sample)->dataLength = 0;
			(*sample)->CTS_Offset = 0;
		}
		return GF_OK;
	}


	if (useEdit==2) {
		if ((SearchMode==GF_ISOM_SEARCH_FORWARD) || (SearchMode==GF_ISOM_SEARCH_BACKWARD)) {

			if (SearchMode==GF_ISOM_SEARCH_FORWARD)
				e = GetNextMediaTime(trak, movieTime, &mediaTime);
			else
				e = GetPrevMediaTime(trak, movieTime, &mediaTime);
			if (e) return e;
			return gf_isom_get_sample_for_movie_time(the_file, trackNumber, (u32) mediaTime, StreamDescriptionIndex, GF_ISOM_SEARCH_SYNC_FORWARD, sample, sampleNumber, data_offset);
		}
	}

	tsscale = trak->Media->mediaHeader->timeScale;
	tsscale /= trak->moov->mvhd->timeScale;


	e = gf_isom_get_sample_for_media_time(the_file, trackNumber, mediaTime, StreamDescriptionIndex, SearchMode, sample, &sampNum, data_offset);
	if (e) {
		if (e==GF_EOS) {
#ifndef GPAC_DISABLE_ISOM_FRAGMENTS

			if (the_file->moov->mvex && !trak->Media->information->sampleTable->SampleSize->sampleCount)
				return e;
#endif

			if (nextMediaTime && (nextMediaTime-1 != movieTime))
				return gf_isom_get_sample_for_movie_time(the_file, trackNumber, nextMediaTime-1, StreamDescriptionIndex, SearchMode, sample, sampleNumber, data_offset);
		}
		return e;
	}


	if (sample && useEdit) {
		u64 _ts = (u64)(segStartTime * tsscale);

		(*sample)->DTS += _ts;

		if ( (*sample)->DTS > (u64) mediaOffset) {
			(*sample)->DTS -= (u64) mediaOffset;
		} else {
			(*sample)->DTS = 0;
		}
	}
	if (sampleNumber) *sampleNumber = sampNum;
#ifndef	GPAC_DISABLE_ISOM_FRAGMENTS
	if (sample && (*sample) ) (*sample)->DTS += trak->dts_at_seg_start;
#endif

	return GF_OK;
}
