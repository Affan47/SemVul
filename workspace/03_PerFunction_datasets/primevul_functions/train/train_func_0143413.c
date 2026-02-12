static struct extent_buffer *alloc_tree_block_no_bg_flush(
					  struct btrfs_trans_handle *trans,
					  struct btrfs_root *root,
					  u64 parent_start,
					  const struct btrfs_disk_key *disk_key,
					  int level,
					  u64 hint,
					  u64 empty_size,
					  enum btrfs_lock_nesting nest)
{
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct extent_buffer *ret;


	if (root == fs_info->extent_root ||
	    root == fs_info->chunk_root ||
	    root == fs_info->dev_root ||
	    root == fs_info->free_space_root)
		trans->can_flush_pending_bgs = false;

	ret = btrfs_alloc_tree_block(trans, root, parent_start,
				     root->root_key.objectid, disk_key, level,
				     hint, empty_size, nest);
	trans->can_flush_pending_bgs = true;

	return ret;
}
