ltr501_show_intensity_scale_avail(struct device *dev,
						 struct device_attribute *attr,
						 char *buf)
{
	struct ltr501_data *data = iio_priv(dev_to_iio_dev(dev));
	struct ltr501_chip_info *info = data->chip_info;
	ssize_t len = 0;
	int i;

	for (i = 0; i < info->als_gain_tbl_size; i++) {
		if (info->als_gain[i].scale == LTR501_RESERVED_GAIN)
			continue;
		len += scnprintf(buf + len, PAGE_SIZE - len, "%d.%06d ",
				 info->als_gain[i].scale,
				 info->als_gain[i].uscale);
	}

	buf[len - 1] = '\n';

	return len;
}
