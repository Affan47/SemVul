int bdev_disk_changed(struct gendisk *disk, bool invalidate)
{
	int ret = 0;

	lockdep_assert_held(&disk->open_mutex);

	if (!disk_live(disk))
		return -ENXIO;

rescan:
	if (disk->open_partitions)
		return -EBUSY;
	sync_blockdev(disk->part0);
	invalidate_bdev(disk->part0);
	blk_drop_partitions(disk);

	clear_bit(GD_NEED_PART_SCAN, &disk->state);


	if (invalidate) {
		if (disk_part_scan_enabled(disk) ||
		    !(disk->flags & GENHD_FL_REMOVABLE))
			set_capacity(disk, 0);
	}

	if (get_capacity(disk)) {
		ret = blk_add_partitions(disk);
		if (ret == -EAGAIN)
			goto rescan;
	} else if (invalidate) {


		kobject_uevent(&disk_to_dev(disk)->kobj, KOBJ_CHANGE);
	}

	return ret;
}
