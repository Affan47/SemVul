int ext4_meta_trans_blocks(struct inode *inode, int nrblocks, int chunk)
{
	int groups, gdpblocks;
	int idxblocks;
	int ret = 0;


	idxblocks = ext4_index_trans_blocks(inode, nrblocks, chunk);

	ret = idxblocks;


	groups = idxblocks;
	if (chunk)
		groups += 1;
	else
		groups += nrblocks;

	gdpblocks = groups;
	if (groups > EXT4_SB(inode->i_sb)->s_groups_count)
		groups = EXT4_SB(inode->i_sb)->s_groups_count;
	if (groups > EXT4_SB(inode->i_sb)->s_gdb_count)
		gdpblocks = EXT4_SB(inode->i_sb)->s_gdb_count;


	ret += groups + gdpblocks;


	ret += EXT4_META_TRANS_BLOCKS(inode->i_sb);

	return ret;
}
