blkid_probe_get_dimension(blkid_probe pr,
		blkid_loff_t *off, blkid_loff_t *size)
{
	if (!pr)
		return -1;

	*off = pr->off;
	*size = pr->size;
	return 0;
}
