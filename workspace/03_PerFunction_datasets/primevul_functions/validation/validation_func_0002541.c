GF_Err Media_FindSyncSample(GF_SampleTableBox *stbl, u32 searchFromSample, u32 *sampleNumber, u8 mode)
{
	GF_ISOSAPType isRAP;
	u32 next, prev, next_in_sap, prev_in_sap;
	if (!stbl || !stbl->SyncSample) return GF_BAD_PARAM;


	*sampleNumber = searchFromSample;


	if ( (mode == GF_ISOM_SEARCH_SYNC_FORWARD) && (searchFromSample == stbl->SampleSize->sampleCount) ) {
		return GF_OK;
	}
	if ( (mode == GF_ISOM_SEARCH_SYNC_BACKWARD) && !searchFromSample) {
		*sampleNumber = 1;
		return GF_OK;
	}

	stbl_GetSampleRAP(stbl->SyncSample, searchFromSample, &isRAP, &prev, &next);
	if (isRAP) {
		(*sampleNumber) = searchFromSample;
		return GF_OK;
	}


	stbl_SearchSAPs(stbl, searchFromSample, &isRAP, &prev_in_sap, &next_in_sap);
	if (isRAP) {
		(*sampleNumber) = searchFromSample;
		return GF_OK;
	}

	if (prev_in_sap > prev)
		prev = prev_in_sap;
	if (next_in_sap && next_in_sap < next)
		next = next_in_sap;


	if (mode == GF_ISOM_SEARCH_SYNC_FORWARD) {
		if (next) *sampleNumber = next;
	} else {
		if (prev) *sampleNumber = prev;
	}

	return GF_OK;
}
