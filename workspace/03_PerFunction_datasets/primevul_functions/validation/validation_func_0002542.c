GF_Err Media_AddSample(GF_MediaBox *mdia, u64 data_offset, const GF_ISOSample *sample, u32 StreamDescIndex, u32 syncShadowNumber)
{
	GF_Err e;
	GF_SampleTableBox *stbl;
	u32 sampleNumber, i;
	if (!mdia || !sample) return GF_BAD_PARAM;

	stbl = mdia->information->sampleTable;


	e = stbl_AddDTS(stbl, sample->DTS, &sampleNumber, mdia->mediaHeader->timeScale, sample->nb_pack);
	if (e) return e;


	e = stbl_AddSize(stbl->SampleSize, sampleNumber, sample->dataLength, sample->nb_pack);
	if (e) return e;


	if (sample->CTS_Offset) {

		if (!stbl->CompositionOffset) {
			stbl->CompositionOffset = (GF_CompositionOffsetBox *) gf_isom_box_new_parent(&stbl->child_boxes, GF_ISOM_BOX_TYPE_CTTS);
			if (!stbl->CompositionOffset) return GF_OUT_OF_MEM;
		}

		e = stbl_AddCTS(stbl, sampleNumber, sample->CTS_Offset);
		if (e) return e;
	} else if (stbl->CompositionOffset) {
		e = stbl_AddCTS(stbl, sampleNumber, sample->CTS_Offset);
		if (e) return e;
	}


	if (sample->IsRAP) {

		if (stbl->SyncSample && (sample->IsRAP == RAP)) {
			e = stbl_AddRAP(stbl->SyncSample, sampleNumber);
			if (e) return e;
		}
	} else {

		if (!stbl->SyncSample) {
			stbl->SyncSample = (GF_SyncSampleBox *) gf_isom_box_new_parent(&stbl->child_boxes, GF_ISOM_BOX_TYPE_STSS);
			if (!stbl->SyncSample) return GF_OUT_OF_MEM;

			for (i=0; i<stbl->SampleSize->sampleCount; i++) {
				if (i+1 != sampleNumber) {
					e = stbl_AddRAP(stbl->SyncSample, i+1);
					if (e) return e;
				}
			}
		}
	}
	if (sample->IsRAP==RAP_REDUNDANT) {
		e = stbl_AddRedundant(stbl, sampleNumber);
		if (e) return e;
	}

	if (!mdia->mediaTrack->chunk_cache) {

		e = stbl_AddChunkOffset(mdia, sampleNumber, StreamDescIndex, data_offset, sample->nb_pack);
		if (e) return e;
	}

	if (!syncShadowNumber) return GF_OK;
	if (!stbl->ShadowSync) {
		stbl->ShadowSync = (GF_ShadowSyncBox *) gf_isom_box_new_parent(&stbl->child_boxes, GF_ISOM_BOX_TYPE_STSH);
		if (!stbl->ShadowSync) return GF_OUT_OF_MEM;
	}
	return stbl_AddShadow(mdia->information->sampleTable->ShadowSync, sampleNumber, syncShadowNumber);
}
