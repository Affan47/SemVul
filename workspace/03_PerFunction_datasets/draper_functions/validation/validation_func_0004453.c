device_flush_capable(struct dm_target *ti, struct dm_dev *dev,
				sector_t start, sector_t len, void *data)
{
	unsigned flush = (*(unsigned *)data);
	struct request_queue *q = bdev_get_queue(dev->bdev);

	return q && (q->flush_flags & flush);
}
