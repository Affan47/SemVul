bitmap_load(struct mddev *mddev)
{
	int err = 0;
	sector_t start = 0;
	sector_t sector = 0;
	struct bitmap *bitmap = mddev->bitmap;

	if (!bitmap)
		goto out;


	while (sector < mddev->resync_max_sectors) {
		sector_t blocks;
		bitmap_start_sync(bitmap, sector, &blocks, 0);
		sector += blocks;
	}
	bitmap_close_sync(bitmap);

	if (mddev->degraded == 0
	    || bitmap->events_cleared == mddev->events)


		start = mddev->recovery_cp;

	mutex_lock(&mddev->bitmap_info.mutex);
	err = bitmap_init_from_disk(bitmap, start);
	mutex_unlock(&mddev->bitmap_info.mutex);

	if (err)
		goto out;
	clear_bit(BITMAP_STALE, &bitmap->flags);


	set_bit(MD_RECOVERY_NEEDED, &bitmap->mddev->recovery);

	mddev->thread->timeout = mddev->bitmap_info.daemon_sleep;
	md_wakeup_thread(mddev->thread);

	bitmap_update_sb(bitmap);

	if (test_bit(BITMAP_WRITE_ERROR, &bitmap->flags))
		err = -EIO;
out:
	return err;
}
