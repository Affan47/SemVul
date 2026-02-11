iio_debugfs_read_reg(struct file *file, char __user *userbuf,
			      size_t count, loff_t *ppos)
{
	struct iio_dev *indio_dev = file->private_data;
	char buf[20];
	unsigned val = 0;
	ssize_t len;
	int ret;

	ret = indio_dev->info->debugfs_reg_access(indio_dev,
						  indio_dev->cached_reg_addr,
						  0, &val);
	if (ret) {
		dev_err(indio_dev->dev.parent, "%s: read failed\n", __func__);
		return ret;
	}

	len = snprintf(buf, sizeof(buf), "0x%X\n", val);

	return simple_read_from_buffer(userbuf, count, ppos, buf, len);
}
