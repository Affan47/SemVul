btrfs_read_roots(struct btrfs_fs_info *fs_info,
			    struct btrfs_root *tree_root)
{
	struct btrfs_root *root;
	struct btrfs_key location;
	int ret;

	location.objectid = BTRFS_EXTENT_TREE_OBJECTID;
	location.type = BTRFS_ROOT_ITEM_KEY;
	location.offset = 0;

	root = btrfs_read_tree_root(tree_root, &location);
	if (IS_ERR(root))
		return PTR_ERR(root);
	set_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state);
	fs_info->extent_root = root;

	location.objectid = BTRFS_DEV_TREE_OBJECTID;
	root = btrfs_read_tree_root(tree_root, &location);
	if (IS_ERR(root))
		return PTR_ERR(root);
	set_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state);
	fs_info->dev_root = root;
	btrfs_init_devices_late(fs_info);

	location.objectid = BTRFS_CSUM_TREE_OBJECTID;
	root = btrfs_read_tree_root(tree_root, &location);
	if (IS_ERR(root))
		return PTR_ERR(root);
	set_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state);
	fs_info->csum_root = root;

	location.objectid = BTRFS_QUOTA_TREE_OBJECTID;
	root = btrfs_read_tree_root(tree_root, &location);
	if (!IS_ERR(root)) {
		set_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state);
		fs_info->quota_enabled = 1;
		fs_info->pending_quota_state = 1;
		fs_info->quota_root = root;
	}

	location.objectid = BTRFS_UUID_TREE_OBJECTID;
	root = btrfs_read_tree_root(tree_root, &location);
	if (IS_ERR(root)) {
		ret = PTR_ERR(root);
		if (ret != -ENOENT)
			return ret;
	} else {
		set_bit(BTRFS_ROOT_TRACK_DIRTY, &root->state);
		fs_info->uuid_root = root;
	}

	return 0;
}
