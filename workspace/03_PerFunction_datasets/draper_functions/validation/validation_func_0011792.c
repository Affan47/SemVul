roccat_common2_sysfs_write(struct file *fp, struct kobject *kobj,
		void const *buf, loff_t off, size_t count,
		size_t real_size, uint command)
{
	struct device *dev =
			container_of(kobj, struct device, kobj)->parent->parent;
	struct roccat_common2_device *roccat_dev = hid_get_drvdata(dev_get_drvdata(dev));
	struct usb_device *usb_dev = interface_to_usbdev(to_usb_interface(dev));
	int retval;

	if (off != 0 || count != real_size)
		return -EINVAL;

	mutex_lock(&roccat_dev->lock);
	retval = roccat_common2_send_with_status(usb_dev, command, buf, real_size);
	mutex_unlock(&roccat_dev->lock);

	return retval ? retval : real_size;
}
