show_status(struct device *dev,
			   struct device_attribute *attr,
			   char *buf)
{
	struct ipath_devdata *dd = dev_get_drvdata(dev);
	ssize_t ret;

	if (!dd->ipath_statusp) {
		ret = -EINVAL;
		goto bail;
	}

	ret = scnprintf(buf, PAGE_SIZE, "0x%llx\n",
			(unsigned long long) *(dd->ipath_statusp));

bail:
	return ret;
}
