static GF_Err UpdateSample(GF_MediaBox *mdia, u32 sampleNumber, u32 size, s32 CTS, u64 offset, u8 isRap)
{
	u32 i;
	GF_SampleTableBox *stbl = mdia->information->sampleTable;


	stbl_SetSampleSize(stbl->SampleSize, sampleNumber, size);
	stbl_SetChunkOffset(mdia, sampleNumber, offset);


	if (stbl->CompositionOffset) {
		stbl_SetSampleCTS(stbl, sampleNumber, CTS);
	} else {

		if (CTS) {
			stbl->CompositionOffset = (GF_CompositionOffsetBox *) gf_isom_box_new_parent(&stbl->child_boxes, GF_ISOM_BOX_TYPE_CTTS);
			if (!stbl->CompositionOffset) return GF_OUT_OF_MEM;
			stbl_AddCTS(stbl, sampleNumber, CTS);
		}
	}

	if (stbl->SyncSample) {
		stbl_SetSampleRAP(stbl->SyncSample, sampleNumber, isRap);
	} else {

		if (! isRap) {
			stbl->SyncSample = (GF_SyncSampleBox *) gf_isom_box_new_parent(&stbl->child_boxes, GF_ISOM_BOX_TYPE_STSS);
			if (!stbl->SyncSample) return GF_OUT_OF_MEM;

			for (i=0; i<stbl->SampleSize->sampleCount; i++) {
				if (i+1 != sampleNumber) stbl_AddRAP(stbl->SyncSample, i+1);
			}
		}
	}
	if (isRap==2) {
		stbl_SetRedundant(stbl, sampleNumber);
	}
	return GF_OK;
}
