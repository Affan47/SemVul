GF_Err stbl_AppendSampleToChunk(GF_SampleTableBox *stbl, u32 DescIndex, u32 samplesInChunk)
{
	u32 nextChunk;
	GF_SampleToChunkBox *stsc= stbl->SampleToChunk;
	GF_StscEntry *ent;

	nextChunk = ((GF_ChunkOffsetBox *) stbl->ChunkOffset)->nb_entries;

	if (stsc->nb_entries) {
		ent = &stsc->entries[stsc->nb_entries-1];

		if ( (ent->sampleDescriptionIndex == DescIndex) && (ent->samplesPerChunk==samplesInChunk))
			return GF_OK;


		ent->nextChunk = nextChunk;
	}
	if (stsc->nb_entries==stsc->alloc_size) {
		ALLOC_INC(stsc->alloc_size);
		stsc->entries = gf_realloc(stsc->entries, sizeof(GF_StscEntry)*stsc->alloc_size);
		if (!stsc->entries) return GF_OUT_OF_MEM;
		memset(&stsc->entries[stsc->nb_entries], 0, sizeof(GF_StscEntry)*(stsc->alloc_size - stsc->nb_entries) );
	}

	ent = &stsc->entries[stsc->nb_entries];
	ent->firstChunk = nextChunk;
	ent->sampleDescriptionIndex = DescIndex;
	ent->samplesPerChunk = samplesInChunk;
	ent->isEdited = 0;
	stsc->nb_entries++;
	return GF_OK;
}
