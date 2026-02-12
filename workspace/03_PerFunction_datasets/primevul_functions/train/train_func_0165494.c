static int ext4_da_get_block_prep(struct inode *inode, sector_t iblock,
				  struct buffer_head *bh_result, int create)
{
	int ret = 0;

	BUG_ON(create == 0);
	BUG_ON(bh_result->b_size != inode->i_sb->s_blocksize);


	ret = ext4_get_blocks_wrap(NULL, inode, iblock, 1,  bh_result, 0, 0, 0);
	if ((ret == 0) && !buffer_delay(bh_result)) {


		ret = ext4_da_reserve_space(inode, 1);
		if (ret)

			return ret;

		map_bh(bh_result, inode->i_sb, 0);
		set_buffer_new(bh_result);
		set_buffer_delay(bh_result);
	} else if (ret > 0) {
		bh_result->b_size = (ret << inode->i_blkbits);
		ret = 0;
	}

	return ret;
}
