GF_Err Media_UpdateSample(GF_MediaBox *mdia, u32 sampleNumber, GF_ISOSample *sample, Bool data_only)
{
	GF_Err e;
	u32 drefIndex, chunkNum, descIndex;
	u64 newOffset, DTS;
	GF_DataEntryURLBox *Dentry;
	GF_SampleTableBox *stbl;

	if (!mdia || !sample || !sampleNumber || !mdia->mediaTrack->moov->mov->editFileMap)
		return GF_BAD_PARAM;

	stbl = mdia->information->sampleTable;

	if (!data_only) {

		e = stbl_GetSampleDTS(stbl->TimeToSample, sampleNumber, &DTS);
		if (e) return e;
		if (DTS != sample->DTS) return GF_BAD_PARAM;
	}


	stbl_GetSampleInfos(stbl, sampleNumber, &newOffset, &chunkNum, &descIndex, NULL);


	e = Media_GetSampleDesc(mdia, descIndex, NULL, &drefIndex);
	if (e) return e;
	Dentry = (GF_DataEntryURLBox*)gf_list_get(mdia->information->dataInformation->dref->child_boxes, drefIndex - 1);
	if (!Dentry) return GF_ISOM_INVALID_FILE;

	if (Dentry->flags != 1) return GF_BAD_PARAM;


	newOffset = gf_isom_datamap_get_offset(mdia->mediaTrack->moov->mov->editFileMap);
	if (sample->dataLength) {
		e = gf_isom_datamap_add_data(mdia->mediaTrack->moov->mov->editFileMap, sample->data, sample->dataLength);
		if (e) return e;
	}

	if (data_only) {
		stbl_SetSampleSize(stbl->SampleSize, sampleNumber, sample->dataLength);
		return stbl_SetChunkOffset(mdia, sampleNumber, newOffset);
	}
	return UpdateSample(mdia, sampleNumber, sample->dataLength, sample->CTS_Offset, newOffset, sample->IsRAP);
}
