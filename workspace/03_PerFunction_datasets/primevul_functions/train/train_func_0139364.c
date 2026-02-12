void btrfs_rm_dev_replace_free_srcdev(struct btrfs_fs_info *fs_info,
				      struct btrfs_device *srcdev)
{
	struct btrfs_fs_devices *fs_devices = srcdev->fs_devices;

	if (test_bit(BTRFS_DEV_STATE_WRITEABLE, &srcdev->dev_state)) {

		btrfs_scratch_superblocks(srcdev->bdev, srcdev->name->str);
	}

	btrfs_close_bdev(srcdev);
	call_rcu(&srcdev->rcu, free_device_rcu);


	if (!fs_devices->num_devices) {
		struct btrfs_fs_devices *tmp_fs_devices;


		ASSERT(fs_devices->seeding);

		tmp_fs_devices = fs_info->fs_devices;
		while (tmp_fs_devices) {
			if (tmp_fs_devices->seed == fs_devices) {
				tmp_fs_devices->seed = fs_devices->seed;
				break;
			}
			tmp_fs_devices = tmp_fs_devices->seed;
		}
		fs_devices->seed = NULL;
		close_fs_devices(fs_devices);
		free_fs_devices(fs_devices);
	}
}
