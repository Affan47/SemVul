register_bdev(struct cache_sb *sb, struct page *sb_page,
				 struct block_device *bdev,
				 struct cached_dev *dc)
{
	char name[BDEVNAME_SIZE];
	const char *err = "cannot allocate memory";
	struct cache_set *c;

	memcpy(&dc->sb, sb, sizeof(struct cache_sb));
	dc->bdev = bdev;
	dc->bdev->bd_holder = dc;

	bio_init(&dc->sb_bio);
	dc->sb_bio.bi_max_vecs	= 1;
	dc->sb_bio.bi_io_vec	= dc->sb_bio.bi_inline_vecs;
	dc->sb_bio.bi_io_vec[0].bv_page = sb_page;
	get_page(sb_page);

	if (cached_dev_init(dc, sb->block_size << 9))
		goto err;

	err = "error creating kobject";
	if (kobject_add(&dc->disk.kobj, &part_to_dev(bdev->bd_part)->kobj,
			"bcache"))
		goto err;
	if (bch_cache_accounting_add_kobjs(&dc->accounting, &dc->disk.kobj))
		goto err;

	pr_info("registered backing device %s", bdevname(bdev, name));

	list_add(&dc->list, &uncached_devices);
	list_for_each_entry(c, &bch_cache_sets, list)
		bch_cached_dev_attach(dc, c);

	if (BDEV_STATE(&dc->sb) == BDEV_STATE_NONE ||
	    BDEV_STATE(&dc->sb) == BDEV_STATE_STALE)
		bch_cached_dev_run(dc);

	return;
err:
	pr_notice("error opening %s: %s", bdevname(bdev, name), err);
	bcache_device_stop(&dc->disk);
}
