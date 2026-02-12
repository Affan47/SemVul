static long btrfs_ioctl_balance(struct file *file, void __user *arg)
{
	struct btrfs_root *root = BTRFS_I(file_inode(file))->root;
	struct btrfs_fs_info *fs_info = root->fs_info;
	struct btrfs_ioctl_balance_args *bargs;
	struct btrfs_balance_control *bctl;
	bool need_unlock;
	int ret;

	if (!capable(CAP_SYS_ADMIN))
		return -EPERM;

	ret = mnt_want_write_file(file);
	if (ret)
		return ret;

again:
	if (!atomic_xchg(&fs_info->mutually_exclusive_operation_running, 1)) {
		mutex_lock(&fs_info->volume_mutex);
		mutex_lock(&fs_info->balance_mutex);
		need_unlock = true;
		goto locked;
	}


	mutex_lock(&fs_info->balance_mutex);
	if (fs_info->balance_ctl) {

		if (!atomic_read(&fs_info->balance_running)) {
			mutex_unlock(&fs_info->balance_mutex);
			if (!mutex_trylock(&fs_info->volume_mutex))
				goto again;
			mutex_lock(&fs_info->balance_mutex);

			if (fs_info->balance_ctl &&
			    !atomic_read(&fs_info->balance_running)) {

				need_unlock = false;
				goto locked;
			}

			mutex_unlock(&fs_info->balance_mutex);
			mutex_unlock(&fs_info->volume_mutex);
			goto again;
		} else {

			mutex_unlock(&fs_info->balance_mutex);
			ret = -EINPROGRESS;
			goto out;
		}
	} else {

		mutex_unlock(&fs_info->balance_mutex);
		ret = BTRFS_ERROR_DEV_EXCL_RUN_IN_PROGRESS;
		goto out;
	}

locked:
	BUG_ON(!atomic_read(&fs_info->mutually_exclusive_operation_running));

	if (arg) {
		bargs = memdup_user(arg, sizeof(*bargs));
		if (IS_ERR(bargs)) {
			ret = PTR_ERR(bargs);
			goto out_unlock;
		}

		if (bargs->flags & BTRFS_BALANCE_RESUME) {
			if (!fs_info->balance_ctl) {
				ret = -ENOTCONN;
				goto out_bargs;
			}

			bctl = fs_info->balance_ctl;
			spin_lock(&fs_info->balance_lock);
			bctl->flags |= BTRFS_BALANCE_RESUME;
			spin_unlock(&fs_info->balance_lock);

			goto do_balance;
		}
	} else {
		bargs = NULL;
	}

	if (fs_info->balance_ctl) {
		ret = -EINPROGRESS;
		goto out_bargs;
	}

	bctl = kzalloc(sizeof(*bctl), GFP_NOFS);
	if (!bctl) {
		ret = -ENOMEM;
		goto out_bargs;
	}

	bctl->fs_info = fs_info;
	if (arg) {
		memcpy(&bctl->data, &bargs->data, sizeof(bctl->data));
		memcpy(&bctl->meta, &bargs->meta, sizeof(bctl->meta));
		memcpy(&bctl->sys, &bargs->sys, sizeof(bctl->sys));

		bctl->flags = bargs->flags;
	} else {

		bctl->flags |= BTRFS_BALANCE_TYPE_MASK;
	}

do_balance:


	need_unlock = false;

	ret = btrfs_balance(bctl, bargs);

	if (arg) {
		if (copy_to_user(arg, bargs, sizeof(*bargs)))
			ret = -EFAULT;
	}

out_bargs:
	kfree(bargs);
out_unlock:
	mutex_unlock(&fs_info->balance_mutex);
	mutex_unlock(&fs_info->volume_mutex);
	if (need_unlock)
		atomic_set(&fs_info->mutually_exclusive_operation_running, 0);
out:
	mnt_drop_write_file(file);
	return ret;
}
