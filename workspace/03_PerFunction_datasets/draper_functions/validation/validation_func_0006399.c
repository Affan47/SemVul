ext2fs_convert_subcluster_bitmap(ext2_filsys fs,
					   ext2fs_block_bitmap *bitmap)
{
	ext2fs_block_bitmap	cmap, bmap;
	errcode_t		retval;
	blk64_t			i, b_end, c_end;
	int			n, ratio;

	bmap = *bitmap;

	if (fs->cluster_ratio_bits == ext2fs_get_bitmap_granularity(bmap))
		return 0;

	retval = ext2fs_allocate_block_bitmap(fs, "converted cluster bitmap",
					      &cmap);
	if (retval)
		return retval;

	i = bmap->start;
	b_end = bmap->end;
	bmap->end = bmap->real_end;
	c_end = cmap->end;
	cmap->end = cmap->real_end;
	n = 0;
	ratio = 1 << fs->cluster_ratio_bits;
	while (i < bmap->real_end) {
		if (ext2fs_test_block_bitmap2(bmap, i)) {
			ext2fs_mark_block_bitmap2(cmap, i);
			i += ratio - n;
			n = 0;
			continue;
		}
		i++; n++;
		if (n >= ratio)
			n = 0;
	}
	bmap->end = b_end;
	cmap->end = c_end;
	ext2fs_free_block_bitmap(bmap);
	*bitmap = cmap;
	return 0;
}
