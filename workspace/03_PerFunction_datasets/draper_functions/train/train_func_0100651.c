btrfs_add_delayed_qgroup_reserve(struct btrfs_fs_info *fs_info,
				     struct btrfs_trans_handle *trans,
				     u64 ref_root, u64 bytenr, u64 num_bytes)
{
	struct btrfs_delayed_ref_root *delayed_refs;
	struct btrfs_delayed_ref_head *ref_head;
	int ret = 0;

	if (!fs_info->quota_enabled || !is_fstree(ref_root))
		return 0;

	delayed_refs = &trans->transaction->delayed_refs;

	spin_lock(&delayed_refs->lock);
	ref_head = find_ref_head(&delayed_refs->href_root, bytenr, 0);
	if (!ref_head) {
		ret = -ENOENT;
		goto out;
	}
	WARN_ON(ref_head->qgroup_reserved || ref_head->qgroup_ref_root);
	ref_head->qgroup_ref_root = ref_root;
	ref_head->qgroup_reserved = num_bytes;
out:
	spin_unlock(&delayed_refs->lock);
	return ret;
}
