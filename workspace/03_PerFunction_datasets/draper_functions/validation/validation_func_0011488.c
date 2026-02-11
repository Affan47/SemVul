aufs_read_unlock(struct dentry *dentry, int flags)
{
	if (au_ftest_lock(flags, DW))
		di_write_unlock(dentry);
	else
		di_read_unlock(dentry, flags);
	si_read_unlock(dentry->d_sb);
}
