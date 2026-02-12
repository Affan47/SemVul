bool f2fs_should_update_inplace(struct inode *inode, struct f2fs_io_info *fio)
{
	if (f2fs_is_pinned_file(inode))
		return true;


	if (file_is_cold(inode))
		return true;

	return check_inplace_update_policy(inode, fio);
}
