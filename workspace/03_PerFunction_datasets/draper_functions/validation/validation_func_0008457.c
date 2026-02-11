afs_getattr(struct vfsmount *mnt, struct dentry *dentry,
		      struct kstat *stat)
{
	struct inode *inode;

	inode = d_inode(dentry);

	_enter("{ ino=%lu v=%u }", inode->i_ino, inode->i_generation);

	generic_fillattr(inode, stat);
	return 0;
}
