static noinline int btrfs_clone_files(struct file *file, struct file *file_src,
					u64 off, u64 olen, u64 destoff)
{
	struct inode *inode = file_inode(file);
	struct inode *src = file_inode(file_src);
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	int ret;
	u64 len = olen;
	u64 bs = fs_info->sb->s_blocksize;


	if (off + len == src->i_size)
		len = ALIGN(src->i_size, bs) - off;

	if (destoff > inode->i_size) {
		const u64 wb_start = ALIGN_DOWN(inode->i_size, bs);

		ret = btrfs_cont_expand(inode, inode->i_size, destoff);
		if (ret)
			return ret;


		ret = btrfs_wait_ordered_range(inode, wb_start,
					       destoff - wb_start);
		if (ret)
			return ret;
	}


	btrfs_double_extent_lock(src, off, inode, destoff, len);
	ret = btrfs_clone(src, inode, off, olen, len, destoff, 0);
	btrfs_double_extent_unlock(src, off, inode, destoff, len);


	truncate_inode_pages_range(&inode->i_data,
				round_down(destoff, PAGE_SIZE),
				round_up(destoff + len, PAGE_SIZE) - 1);

	return ret;
}
