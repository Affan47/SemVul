__load_block_bitmap(struct super_block *sb,
			       struct udf_bitmap *bitmap,
			       unsigned int block_group)
{
	int retval = 0;
	int nr_groups = bitmap->s_nr_groups;

	if (block_group >= nr_groups) {
		udf_debug("block_group (%d) > nr_groups (%d)\n",
			  block_group, nr_groups);
	}

	if (bitmap->s_block_bitmap[block_group])
		return block_group;

	retval = read_block_bitmap(sb, bitmap, block_group, block_group);
	if (retval < 0)
		return retval;

	return block_group;
}
