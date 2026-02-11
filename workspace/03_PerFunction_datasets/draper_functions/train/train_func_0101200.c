ubifs_unlink(struct inode *dir, struct dentry *dentry)
{
	struct ubifs_info *c = dir->i_sb->s_fs_info;
	struct inode *inode = d_inode(dentry);
	struct ubifs_inode *dir_ui = ubifs_inode(dir);
	int sz_change = CALC_DENT_SIZE(dentry->d_name.len);
	int err, budgeted = 1;
	struct ubifs_budget_req req = { .mod_dent = 1, .dirtied_ino = 2 };
	unsigned int saved_nlink = inode->i_nlink;


	dbg_gen("dent '%pd' from ino %lu (nlink %d) in dir ino %lu",
		dentry, inode->i_ino,
		inode->i_nlink, dir->i_ino);
	ubifs_assert(mutex_is_locked(&dir->i_mutex));
	ubifs_assert(mutex_is_locked(&inode->i_mutex));
	err = dbg_check_synced_i_size(c, inode);
	if (err)
		return err;

	err = ubifs_budget_space(c, &req);
	if (err) {
		if (err != -ENOSPC)
			return err;
		budgeted = 0;
	}

	lock_2_inodes(dir, inode);
	inode->i_ctime = ubifs_current_time(dir);
	drop_nlink(inode);
	dir->i_size -= sz_change;
	dir_ui->ui_size = dir->i_size;
	dir->i_mtime = dir->i_ctime = inode->i_ctime;
	err = ubifs_jnl_update(c, dir, &dentry->d_name, inode, 1, 0);
	if (err)
		goto out_cancel;
	unlock_2_inodes(dir, inode);

	if (budgeted)
		ubifs_release_budget(c, &req);
	else {

		c->bi.nospace = c->bi.nospace_rp = 0;
		smp_wmb();
	}
	return 0;

out_cancel:
	dir->i_size += sz_change;
	dir_ui->ui_size = dir->i_size;
	set_nlink(inode, saved_nlink);
	unlock_2_inodes(dir, inode);
	if (budgeted)
		ubifs_release_budget(c, &req);
	return err;
}
