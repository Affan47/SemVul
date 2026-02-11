_add_bloom(struct sst *sst, int fd, int count)
{
	int i;
	int blk_sizes;
	struct sst_block *blks;

	blk_sizes = count * sizeof(struct sst_block);

	blks= mmap(0, blk_sizes, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if (blks == MAP_FAILED) {
		__DEBUG(LEVEL_ERROR, "%s", "add_bloom, mmapping the file");
		return;
	}

	for (i = 0; i < count; i++)
		bloom_add(sst->bloom, blks[i].key);

	if (munmap(blks, blk_sizes) == -1)
		__DEBUG(LEVEL_ERROR, "%s", "Error:sst_bloom un-mmapping the file");
}
