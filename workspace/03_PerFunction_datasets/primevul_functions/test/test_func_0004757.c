static noinline int init_first_rw_device(struct btrfs_trans_handle *trans)
{
	struct btrfs_fs_info *fs_info = trans->fs_info;
	u64 alloc_profile;
	struct btrfs_block_group *meta_bg;
	struct btrfs_block_group *sys_bg;


	alloc_profile = btrfs_metadata_alloc_profile(fs_info);
	meta_bg = btrfs_alloc_chunk(trans, alloc_profile);
	if (IS_ERR(meta_bg))
		return PTR_ERR(meta_bg);

	alloc_profile = btrfs_system_alloc_profile(fs_info);
	sys_bg = btrfs_alloc_chunk(trans, alloc_profile);
	if (IS_ERR(sys_bg))
		return PTR_ERR(sys_bg);

	return 0;
}
