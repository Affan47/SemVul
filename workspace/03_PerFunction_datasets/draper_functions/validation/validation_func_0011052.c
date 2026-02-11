nilfs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct nilfs_transaction_info ti;
	int err;

	err = nilfs_transaction_begin(dir->i_sb, &ti, 0);
	if (err)
		return err;

	err = nilfs_do_unlink(dir, dentry);

	if (!err) {
		nilfs_mark_inode_dirty(dir);
		nilfs_mark_inode_dirty(d_inode(dentry));
		err = nilfs_transaction_commit(dir->i_sb);
	} else
		nilfs_transaction_abort(dir->i_sb);

	return err;
}
