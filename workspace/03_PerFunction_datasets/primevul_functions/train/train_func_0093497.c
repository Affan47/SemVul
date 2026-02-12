static int avi_add_std_index(avi_t *AVI, unsigned char *idxtag, unsigned char *strtag,
                             avistdindex_chunk *stdil)
{

	memcpy (stdil->fcc, idxtag, 4);
	stdil->dwSize = 4096;
	stdil->wLongsPerEntry = 2;
	stdil->bIndexSubType = 0;
	stdil->bIndexType = AVI_INDEX_OF_CHUNKS;
	stdil->nEntriesInUse = 0;


	memcpy(stdil->dwChunkId, strtag, 4);


	stdil->aIndex = (avistdindex_entry *)gf_malloc(stdil->dwSize * sizeof (u32) * stdil->wLongsPerEntry);

	if (!stdil->aIndex) {
		AVI_errno = AVI_ERR_NO_MEM;
		return -1;
	}


	return 0;
}
