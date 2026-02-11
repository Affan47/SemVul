__add_dirty_inode(struct inode *inode, struct inode_entry *new)
{
	struct f2fs_sb_info *sbi = F2FS_I_SB(inode);

	if (is_inode_flag_set(F2FS_I(inode), FI_DIRTY_DIR))
		return -EEXIST;

	set_inode_flag(F2FS_I(inode), FI_DIRTY_DIR);
	F2FS_I(inode)->dirty_dir = new;
	list_add_tail(&new->list, &sbi->dir_inode_list);
	stat_inc_dirty_dir(sbi);
	return 0;
}
