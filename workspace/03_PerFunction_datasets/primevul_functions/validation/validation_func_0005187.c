GF_Err stbl_SetChunkAndOffset(GF_SampleTableBox *stbl, u32 sampleNumber, u32 StreamDescIndex, GF_SampleToChunkBox *the_stsc, GF_Box **the_stco, u64 data_offset, Bool forceNewChunk, u32 nb_samp)
{
	GF_Err e;
	u8 newChunk;
	GF_StscEntry *newEnt, *cur_ent;

	if (!stbl) return GF_ISOM_INVALID_FILE;

	newChunk = 0;


	if (forceNewChunk) newChunk = 1;

	cur_ent = NULL;

	if (! the_stsc->entries) {
		newChunk = 1;
	} else {
		cur_ent = &the_stsc->entries[the_stsc->nb_entries - 1];

		if (StreamDescIndex != cur_ent->sampleDescriptionIndex)
			newChunk = 1;
		if (stbl->MaxSamplePerChunk && cur_ent->samplesPerChunk >= stbl->MaxSamplePerChunk)
			newChunk = 1;
	}


	if (!newChunk) {
		cur_ent->samplesPerChunk += nb_samp;
		return GF_OK;
	}


	if (the_stsc->nb_entries > 1) {
		GF_StscEntry *ent = &the_stsc->entries[the_stsc->nb_entries - 2];
		if (!ent) return GF_OUT_OF_MEM;
		if ( (ent->sampleDescriptionIndex == cur_ent->sampleDescriptionIndex)
		        && (ent->samplesPerChunk == cur_ent->samplesPerChunk)
		   ) {

			ent->nextChunk = cur_ent->firstChunk;
			the_stsc->nb_entries--;
		}
	}


	e = stbl_AddOffset(stbl, the_stco, data_offset);
	if (e) return e;

	if (the_stsc->nb_entries==the_stsc->alloc_size) {
		ALLOC_INC(the_stsc->alloc_size);
		the_stsc->entries = gf_realloc(the_stsc->entries, sizeof(GF_StscEntry)*the_stsc->alloc_size);
		if (!the_stsc->entries) return GF_OUT_OF_MEM;
		memset(&the_stsc->entries[the_stsc->nb_entries], 0, sizeof(GF_StscEntry)*(the_stsc->alloc_size-the_stsc->nb_entries));
	}

	newEnt = &the_stsc->entries[the_stsc->nb_entries];
	if (!newEnt) return GF_OUT_OF_MEM;


	if ((*the_stco)->type == GF_ISOM_BOX_TYPE_STCO) {
		newEnt->firstChunk = ((GF_ChunkOffsetBox *) (*the_stco) )->nb_entries;
	} else {
		newEnt->firstChunk = ((GF_ChunkLargeOffsetBox *) (*the_stco) )->nb_entries;
	}
	newEnt->sampleDescriptionIndex = StreamDescIndex;
	newEnt->samplesPerChunk = nb_samp;
	newEnt->nextChunk = 0;

	if (the_stsc->nb_entries)
		the_stsc->entries[the_stsc->nb_entries-1].nextChunk = newEnt->firstChunk;
	the_stsc->nb_entries++;
	return GF_OK;
}
