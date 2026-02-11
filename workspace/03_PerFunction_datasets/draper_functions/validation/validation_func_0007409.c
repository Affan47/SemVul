shmem_rmdir(struct inode *dir, struct dentry *dentry)
{
	if (!simple_empty(dentry))
		return -ENOTEMPTY;

	drop_nlink(d_inode(dentry));
	drop_nlink(dir);
	return shmem_unlink(dir, dentry);
}
