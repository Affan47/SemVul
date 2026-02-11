cbm_write(struct exfat_dev* dev)
{
	uint32_t allocated_clusters =
			DIV_ROUND_UP(cbm.get_size(), get_cluster_size()) +
			DIV_ROUND_UP(uct.get_size(), get_cluster_size()) +
			DIV_ROUND_UP(rootdir.get_size(), get_cluster_size());
	size_t bitmap_size = DIV_ROUND_UP(allocated_clusters, CHAR_BIT);
	uint8_t* bitmap = malloc(bitmap_size);
	size_t i;

	if (bitmap == NULL)
	{
		exfat_error("failed to allocate bitmap of %zu bytes", bitmap_size);
		return 1;
	}

	for (i = 0; i < bitmap_size * CHAR_BIT; i++)
		if (i < allocated_clusters)
			BMAP_SET(bitmap, i);
		else
			BMAP_CLR(bitmap, i);
	if (exfat_write(dev, bitmap, bitmap_size) < 0)
	{
		exfat_error("failed to write bitmap of %zu bytes", bitmap_size);
		return 1;
	}
	free(bitmap);
	return 0;
}
