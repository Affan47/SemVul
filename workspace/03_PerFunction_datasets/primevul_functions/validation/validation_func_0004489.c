GF_Err stbl_GetSampleCTS(GF_CompositionOffsetBox *ctts, u32 SampleNumber, s32 *CTSoffset)
{
	u32 i;

	(*CTSoffset) = 0;

	if (!ctts || !SampleNumber) return GF_BAD_PARAM;

	if (ctts->r_FirstSampleInEntry && (ctts->r_FirstSampleInEntry < SampleNumber) ) {
		i = ctts->r_currentEntryIndex;
	} else {
		ctts->r_FirstSampleInEntry = 1;
		ctts->r_currentEntryIndex = 0;
		i = 0;
	}
	for (; i< ctts->nb_entries; i++) {
		if (SampleNumber < ctts->r_FirstSampleInEntry + ctts->entries[i].sampleCount) break;

		ctts->r_currentEntryIndex += 1;
		ctts->r_FirstSampleInEntry += ctts->entries[i].sampleCount;
	}

	if (i==ctts->nb_entries) return GF_OK;

	if (SampleNumber >= ctts->r_FirstSampleInEntry + ctts->entries[i].sampleCount) return GF_OK;
	(*CTSoffset) = ctts->entries[i].decodingOffset;
	return GF_OK;
}
