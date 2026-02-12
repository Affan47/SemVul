static int avi_add_odml_index_entry_core(avi_t *AVI, int flags, u64 pos, unsigned int len, avistdindex_chunk *si)
{
	u32 cur_chunk_idx;

	si->nEntriesInUse++;
	cur_chunk_idx = si->nEntriesInUse-1;


	if (cur_chunk_idx >= si->dwSize) {
		si->dwSize += 4096;
		si->aIndex = (avistdindex_entry *)gf_realloc ( si->aIndex, si->dwSize * sizeof (u32) * si->wLongsPerEntry);
	}

	if(len>AVI->max_len) AVI->max_len=len;


	if (flags != 0x10) {
		len |= 0x80000000;
	}

	si->aIndex [ cur_chunk_idx ].dwSize = len;
	si->aIndex [ cur_chunk_idx ].dwOffset = (u32) (pos - si->qwBaseOffset + 8);


	return 0;
}
