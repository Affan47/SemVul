xlvbd_alloc_gendisk(blkif_sector_t capacity,
			       struct blkfront_info *info,
			       u16 vdisk_info, u16 sector_size,
			       unsigned int physical_sector_size)
{
	struct gendisk *gd;
	int nr_minors = 1;
	int err;
	unsigned int offset;
	int minor;
	int nr_parts;
	char *ptr;

	BUG_ON(info->gd != NULL);
	BUG_ON(info->rq != NULL);

	if ((info->vdevice>>EXT_SHIFT) > 1) {

		printk(KERN_WARNING "blkfront: vdevice 0x%x is above the extended range; ignoring\n", info->vdevice);
		return -ENODEV;
	}

	if (!VDEV_IS_EXTENDED(info->vdevice)) {
		err = xen_translate_vdev(info->vdevice, &minor, &offset);
		if (err)
			return err;
 		nr_parts = PARTS_PER_DISK;
	} else {
		minor = BLKIF_MINOR_EXT(info->vdevice);
		nr_parts = PARTS_PER_EXT_DISK;
		offset = minor / nr_parts;
		if (xen_hvm_domain() && offset < EMULATED_HD_DISK_NAME_OFFSET + 4)
			printk(KERN_WARNING "blkfront: vdevice 0x%x might conflict with "
					"emulated IDE disks,\n\t choose an xvd device name"
					"from xvde on\n", info->vdevice);
	}
	if (minor >> MINORBITS) {
		pr_warn("blkfront: %#x's minor (%#x) out of range; ignoring\n",
			info->vdevice, minor);
		return -ENODEV;
	}

	if ((minor % nr_parts) == 0)
		nr_minors = nr_parts;

	err = xlbd_reserve_minors(minor, nr_minors);
	if (err)
		goto out;
	err = -ENODEV;

	gd = alloc_disk(nr_minors);
	if (gd == NULL)
		goto release;

	strcpy(gd->disk_name, DEV_NAME);
	ptr = encode_disk_name(gd->disk_name + sizeof(DEV_NAME) - 1, offset);
	BUG_ON(ptr >= gd->disk_name + DISK_NAME_LEN);
	if (nr_minors > 1)
		*ptr = 0;
	else
		snprintf(ptr, gd->disk_name + DISK_NAME_LEN - ptr,
			 "%d", minor & (nr_parts - 1));

	gd->major = XENVBD_MAJOR;
	gd->first_minor = minor;
	gd->fops = &xlvbd_block_fops;
	gd->private_data = info;
	gd->driverfs_dev = &(info->xbdev->dev);
	set_capacity(gd, capacity);

	if (xlvbd_init_blk_queue(gd, sector_size, physical_sector_size,
				 info->max_indirect_segments ? :
				 BLKIF_MAX_SEGMENTS_PER_REQUEST)) {
		del_gendisk(gd);
		goto release;
	}

	info->rq = gd->queue;
	info->gd = gd;

	xlvbd_flush(info);

	if (vdisk_info & VDISK_READONLY)
		set_disk_ro(gd, 1);

	if (vdisk_info & VDISK_REMOVABLE)
		gd->flags |= GENHD_FL_REMOVABLE;

	if (vdisk_info & VDISK_CDROM)
		gd->flags |= GENHD_FL_CD;

	return 0;

 release:
	xlbd_release_minors(minor, nr_minors);
 out:
	return err;
}
