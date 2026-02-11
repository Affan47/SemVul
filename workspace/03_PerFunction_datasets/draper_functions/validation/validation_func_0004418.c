jffs2_rmdir (struct inode *dir_i, struct dentry *dentry)
{
	struct jffs2_sb_info *c = JFFS2_SB_INFO(dir_i->i_sb);
	struct jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	struct jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode(dentry));
	struct jffs2_full_dirent *fd;
	int ret;
	uint32_t now = get_seconds();

	for (fd = f->dents ; fd; fd = fd->next) {
		if (fd->ino)
			return -ENOTEMPTY;
	}

	ret = jffs2_do_unlink(c, dir_f, dentry->d_name.name,
			      dentry->d_name.len, f, now);
	if (!ret) {
		dir_i->i_mtime = dir_i->i_ctime = ITIME(now);
		clear_nlink(d_inode(dentry));
		drop_nlink(dir_i);
	}
	return ret;
}
