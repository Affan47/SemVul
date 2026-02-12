int ext4_change_inode_journal_flag(struct inode *inode, int val)
{
	journal_t *journal;
	handle_t *handle;
	int err;
	struct ext4_sb_info *sbi = EXT4_SB(inode->i_sb);


	journal = EXT4_JOURNAL(inode);
	if (!journal)
		return 0;
	if (is_journal_aborted(journal))
		return -EROFS;


	inode_dio_wait(inode);


	if (val) {
		down_write(&EXT4_I(inode)->i_mmap_sem);
		err = filemap_write_and_wait(inode->i_mapping);
		if (err < 0) {
			up_write(&EXT4_I(inode)->i_mmap_sem);
			return err;
		}
	}

	percpu_down_write(&sbi->s_journal_flag_rwsem);
	jbd2_journal_lock_updates(journal);


	if (val)
		ext4_set_inode_flag(inode, EXT4_INODE_JOURNAL_DATA);
	else {
		err = jbd2_journal_flush(journal);
		if (err < 0) {
			jbd2_journal_unlock_updates(journal);
			percpu_up_write(&sbi->s_journal_flag_rwsem);
			return err;
		}
		ext4_clear_inode_flag(inode, EXT4_INODE_JOURNAL_DATA);
	}
	ext4_set_aops(inode);

	jbd2_journal_unlock_updates(journal);
	percpu_up_write(&sbi->s_journal_flag_rwsem);

	if (val)
		up_write(&EXT4_I(inode)->i_mmap_sem);


	handle = ext4_journal_start(inode, EXT4_HT_INODE, 1);
	if (IS_ERR(handle))
		return PTR_ERR(handle);

	err = ext4_mark_inode_dirty(handle, inode);
	ext4_handle_sync(handle);
	ext4_journal_stop(handle);
	ext4_std_error(inode->i_sb, err);

	return err;
}
