ssd_save_log(struct ssd_device *dev, struct ssd_log *log)
{
	uint32_t off, size;
	void *internal_log;
	int ret = 0;

	mutex_lock(&dev->internal_log_mutex);

	size = sizeof(struct ssd_log);
	off = dev->internal_log.nr_log * size;

	if (off == dev->rom_info.log_sz) {
		if (dev->internal_log.nr_log == dev->smart.log_info.nr_log) {
			hio_warn("%s: internal log is full\n", dev->name);
		}
		goto out;
	}

	internal_log = dev->internal_log.log + off;
	memcpy(internal_log, log, size);

	if (dev->protocol_info.ver > SSD_PROTOCOL_V3) {
		off += dev->rom_info.log_base;

		ret = ssd_spi_write(dev, log, off, size);
		if (ret) {
			goto out;
		}
	}

	dev->internal_log.nr_log++;

out:
	mutex_unlock(&dev->internal_log_mutex);
	return ret;
}
