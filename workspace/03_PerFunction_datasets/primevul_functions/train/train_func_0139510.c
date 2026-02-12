static int btrfs_extent_same_range(struct inode *src, u64 loff, u64 olen,
				   struct inode *dst, u64 dst_loff)
{
	u64 bs = BTRFS_I(src)->root->fs_info->sb->s_blocksize;
	int ret;
	u64 len = olen;

	if (loff + len == src->i_size)
		len = ALIGN(src->i_size, bs) - loff;


	if (dst == src && len != olen)
		return -EINVAL;


	btrfs_double_extent_lock(src, loff, dst, dst_loff, len);
	ret = btrfs_clone(src, dst, loff, olen, len, dst_loff, 1);
	btrfs_double_extent_unlock(src, loff, dst, dst_loff, len);

	return ret;
}
