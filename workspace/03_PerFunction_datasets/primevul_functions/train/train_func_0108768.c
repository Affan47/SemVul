static ssize_t ext4_direct_IO_write(struct kiocb *iocb, struct iov_iter *iter)
{
	struct file *file = iocb->ki_filp;
	struct inode *inode = file->f_mapping->host;
	struct ext4_inode_info *ei = EXT4_I(inode);
	ssize_t ret;
	loff_t offset = iocb->ki_pos;
	size_t count = iov_iter_count(iter);
	int overwrite = 0;
	get_block_t *get_block_func = NULL;
	int dio_flags = 0;
	loff_t final_size = offset + count;
	int orphan = 0;
	handle_t *handle;

	if (final_size > inode->i_size || final_size > ei->i_disksize) {

		handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
		if (IS_ERR(handle)) {
			ret = PTR_ERR(handle);
			goto out;
		}
		ret = ext4_orphan_add(handle, inode);
		if (ret) {
			ext4_journal_stop(handle);
			goto out;
		}
		orphan = 1;
		ext4_update_i_disksize(inode, inode->i_size);
		ext4_journal_stop(handle);
	}

	BUG_ON(iocb->private == NULL);


	inode_dio_begin(inode);


	overwrite = *((int *)iocb->private);

	if (overwrite)
		inode_unlock(inode);


	iocb->private = NULL;
	if (overwrite)
		get_block_func = ext4_dio_get_block_overwrite;
	else if (!ext4_test_inode_flag(inode, EXT4_INODE_EXTENTS) ||
		   round_down(offset, i_blocksize(inode)) >= inode->i_size) {
		get_block_func = ext4_dio_get_block;
		dio_flags = DIO_LOCKING | DIO_SKIP_HOLES;
	} else if (is_sync_kiocb(iocb)) {
		get_block_func = ext4_dio_get_block_unwritten_sync;
		dio_flags = DIO_LOCKING;
	} else {
		get_block_func = ext4_dio_get_block_unwritten_async;
		dio_flags = DIO_LOCKING;
	}
	ret = __blockdev_direct_IO(iocb, inode, inode->i_sb->s_bdev, iter,
				   get_block_func, ext4_end_io_dio, NULL,
				   dio_flags);

	if (ret > 0 && !overwrite && ext4_test_inode_state(inode,
						EXT4_STATE_DIO_UNWRITTEN)) {
		int err;


		err = ext4_convert_unwritten_extents(NULL, inode,
						     offset, ret);
		if (err < 0)
			ret = err;
		ext4_clear_inode_state(inode, EXT4_STATE_DIO_UNWRITTEN);
	}

	inode_dio_end(inode);

	if (overwrite)
		inode_lock(inode);

	if (ret < 0 && final_size > inode->i_size)
		ext4_truncate_failed_write(inode);


	if (orphan) {
		int err;


		handle = ext4_journal_start(inode, EXT4_HT_INODE, 2);
		if (IS_ERR(handle)) {


			if (!ret)
				ret = PTR_ERR(handle);
			if (inode->i_nlink)
				ext4_orphan_del(NULL, inode);

			goto out;
		}
		if (inode->i_nlink)
			ext4_orphan_del(handle, inode);
		if (ret > 0) {
			loff_t end = offset + ret;
			if (end > inode->i_size || end > ei->i_disksize) {
				ext4_update_i_disksize(inode, end);
				if (end > inode->i_size)
					i_size_write(inode, end);


				ext4_mark_inode_dirty(handle, inode);
			}
		}
		err = ext4_journal_stop(handle);
		if (ret == 0)
			ret = err;
	}
out:
	return ret;
}
