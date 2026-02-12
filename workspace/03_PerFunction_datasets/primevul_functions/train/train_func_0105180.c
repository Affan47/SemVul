static int adu_release(struct inode *inode, struct file *file)
{
	struct adu_device *dev;
	int retval = 0;

	if (file == NULL) {
		retval = -ENODEV;
		goto exit;
	}

	dev = file->private_data;
	if (dev == NULL) {
		retval = -ENODEV;
		goto exit;
	}

	mutex_lock(&adutux_mutex);

	if (dev->open_count <= 0) {
		dev_dbg(&dev->udev->dev, "%s : device not opened\n", __func__);
		retval = -ENODEV;
		goto unlock;
	}

	adu_release_internal(dev);
	if (dev->udev == NULL) {

		if (!dev->open_count)
			adu_delete(dev);
	}
unlock:
	mutex_unlock(&adutux_mutex);
exit:
	return retval;
}
