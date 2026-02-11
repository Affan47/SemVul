raid0_congested(struct mddev *mddev, int bits)
{
	struct r0conf *conf = mddev->private;
	struct md_rdev **devlist = conf->devlist;
	int raid_disks = conf->strip_zone[0].nb_dev;
	int i, ret = 0;

	for (i = 0; i < raid_disks && !ret ; i++) {
		struct request_queue *q = bdev_get_queue(devlist[i]->bdev);

		ret |= bdi_congested(q->backing_dev_info, bits);
	}
	return ret;
}
