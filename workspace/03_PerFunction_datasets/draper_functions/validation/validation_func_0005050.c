fatWriteSector(Fs_t *This, int sector, int slot, int bit, int dupe)
{
	int fat_start;

	dupe = (dupe + This->primaryFat) % This->num_fat;
	if(dupe && !This->writeAllFats)
		return This->sector_size;

	fat_start = This->fat_start + This->fat_len * dupe;

	return forceWriteSector(This,
				(char *)
				(This->FatMap[slot].data + bit * This->sector_size),
				fat_start+sector, 1);
}
