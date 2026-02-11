btrfs_qgroup_rescan_worker(struct btrfs_work *work)
{
	struct btrfs_fs_info *fs_info = container_of(work, struct btrfs_fs_info,
						     qgroup_rescan_work);
	struct btrfs_path *path;
	struct btrfs_trans_handle *trans = NULL;
	int err = -ENOMEM;
	int ret = 0;

	path = btrfs_alloc_path();
	if (!path)
		goto out;

	err = 0;
	while (!err && !btrfs_fs_closing(fs_info)) {
		trans = btrfs_start_transaction(fs_info->fs_root, 0);
		if (IS_ERR(trans)) {
			err = PTR_ERR(trans);
			break;
		}
		if (!fs_info->quota_enabled) {
			err = -EINTR;
		} else {
			err = qgroup_rescan_leaf(fs_info, path, trans);
		}
		if (err > 0)
			btrfs_commit_transaction(trans, fs_info->fs_root);
		else
			btrfs_end_transaction(trans, fs_info->fs_root);
	}

out:
	btrfs_free_path(path);

	mutex_lock(&fs_info->qgroup_rescan_lock);
	if (!btrfs_fs_closing(fs_info))
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_RESCAN;

	if (err > 0 &&
	    fs_info->qgroup_flags & BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT) {
		fs_info->qgroup_flags &= ~BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	} else if (err < 0) {
		fs_info->qgroup_flags |= BTRFS_QGROUP_STATUS_FLAG_INCONSISTENT;
	}
	mutex_unlock(&fs_info->qgroup_rescan_lock);


	trans = btrfs_start_transaction(fs_info->quota_root, 1);
	if (IS_ERR(trans)) {
		err = PTR_ERR(trans);
		btrfs_err(fs_info,
			  "fail to start transaction for status update: %d\n",
			  err);
		goto done;
	}
	ret = update_qgroup_status_item(trans, fs_info, fs_info->quota_root);
	if (ret < 0) {
		err = ret;
		btrfs_err(fs_info, "fail to update qgroup status: %d\n", err);
	}
	btrfs_end_transaction(trans, fs_info->quota_root);

	if (btrfs_fs_closing(fs_info)) {
		btrfs_info(fs_info, "qgroup scan paused");
	} else if (err >= 0) {
		btrfs_info(fs_info, "qgroup scan completed%s",
			err > 0 ? " (inconsistency flag cleared)" : "");
	} else {
		btrfs_err(fs_info, "qgroup scan failed with %d", err);
	}

done:
	mutex_lock(&fs_info->qgroup_rescan_lock);
	fs_info->qgroup_rescan_running = false;
	mutex_unlock(&fs_info->qgroup_rescan_lock);
	complete_all(&fs_info->qgroup_rescan_completion);
}
