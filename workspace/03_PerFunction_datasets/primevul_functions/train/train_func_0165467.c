int ext4_get_blocks_wrap(handle_t *handle, struct inode *inode, sector_t block,
			unsigned int max_blocks, struct buffer_head *bh,
			int create, int extend_disksize, int flag)
{
	int retval;

	clear_buffer_mapped(bh);


	down_read((&EXT4_I(inode)->i_data_sem));
	if (EXT4_I(inode)->i_flags & EXT4_EXTENTS_FL) {
		retval =  ext4_ext_get_blocks(handle, inode, block, max_blocks,
				bh, 0, 0);
	} else {
		retval = ext4_get_blocks_handle(handle,
				inode, block, max_blocks, bh, 0, 0);
	}
	up_read((&EXT4_I(inode)->i_data_sem));


	if (!create)
		return retval;


	if (retval > 0 && buffer_mapped(bh))
		return retval;


	down_write((&EXT4_I(inode)->i_data_sem));


	if (flag)
		EXT4_I(inode)->i_delalloc_reserved_flag = 1;


	if (EXT4_I(inode)->i_flags & EXT4_EXTENTS_FL) {
		retval =  ext4_ext_get_blocks(handle, inode, block, max_blocks,
				bh, create, extend_disksize);
	} else {
		retval = ext4_get_blocks_handle(handle, inode, block,
				max_blocks, bh, create, extend_disksize);

		if (retval > 0 && buffer_new(bh)) {


			EXT4_I(inode)->i_flags = EXT4_I(inode)->i_flags &
							~EXT4_EXT_MIGRATE;
		}
	}

	if (flag) {
		EXT4_I(inode)->i_delalloc_reserved_flag = 0;


		if ((retval > 0) && buffer_delay(bh))
			ext4_da_update_reserve_space(inode, retval);
	}

	up_write((&EXT4_I(inode)->i_data_sem));
	return retval;
}
