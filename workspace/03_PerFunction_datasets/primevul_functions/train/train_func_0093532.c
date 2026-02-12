static int avi_ixnn_entry(avi_t *AVI, avistdindex_chunk *ch, avisuperindex_entry *en)
{
	int bl;
	u32 k;
	unsigned int max = ch->nEntriesInUse * sizeof (u32) * ch->wLongsPerEntry + 24;
	char *ix00 = (char *)gf_malloc (max);
	char dfcc[5];
	memcpy (dfcc, ch->fcc, 4);
	dfcc[4] = 0;

	bl = 0;

	if (en) {
		en->qwOffset = AVI->pos;
		en->dwSize = max;

	}

#ifdef DEBUG_ODML

#endif


	OUTW(ch->wLongsPerEntry);
	OUTC(ch->bIndexSubType);
	OUTC(ch->bIndexType);
	OUTD(ch->nEntriesInUse);
	OUTS(ch->dwChunkId);
	OUTD(ch->qwBaseOffset&0xffffffff);
	OUTD((ch->qwBaseOffset>>32)&0xffffffff);
	OUTD(ch->dwReserved3);

	for (k = 0; k < ch->nEntriesInUse; k++) {
		OUTD(ch->aIndex[k].dwOffset);
		OUTD(ch->aIndex[k].dwSize);

	}
	avi_add_chunk (AVI, (unsigned char*)ch->fcc, (unsigned char*)ix00, max);

	gf_free(ix00);

	return 0;
}
