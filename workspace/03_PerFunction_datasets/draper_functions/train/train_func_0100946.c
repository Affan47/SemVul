read_report_descriptor(struct file *filp, struct kobject *kobj,
		struct bin_attribute *attr,
		char *buf, loff_t off, size_t count)
{
	struct device *dev = container_of(kobj, struct device, kobj);
	struct hid_device *hdev = container_of(dev, struct hid_device, dev);

	if (off >= hdev->rsize)
		return 0;

	if (off + count > hdev->rsize)
		count = hdev->rsize - off;

	memcpy(buf, hdev->rdesc + off, count);

	return count;
}
