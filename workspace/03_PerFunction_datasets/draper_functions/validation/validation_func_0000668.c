update_time_for_write(struct inode *inode)
{
	struct timespec now;

	if (IS_NOCMTIME(inode))
		return;

	now = current_fs_time(inode->i_sb);
	if (!timespec_equal(&inode->i_mtime, &now))
		inode->i_mtime = now;

	if (!timespec_equal(&inode->i_ctime, &now))
		inode->i_ctime = now;

	if (IS_I_VERSION(inode))
		inode_inc_iversion(inode);
}
