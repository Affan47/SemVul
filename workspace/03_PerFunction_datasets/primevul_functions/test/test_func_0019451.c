int jfs_write_inode(struct inode *inode, struct writeback_control *wbc)
{
	int wait = wbc->sync_mode == WB_SYNC_ALL;

	if (inode->i_nlink == 0)
		return 0;


	if (!test_cflag(COMMIT_Dirty, inode)) {

		jfs_flush_journal(JFS_SBI(inode->i_sb)->log, wait);
		return 0;
	}

	if (jfs_commit_inode(inode, wait)) {
		jfs_err("jfs_write_inode: jfs_commit_inode failed!");
		return -EIO;
	} else
		return 0;
}
