flash_fault_show(struct device *dev,
		struct device_attribute *attr, char *buf)
{
	struct led_classdev *led_cdev = dev_get_drvdata(dev);
	struct led_classdev_flash *fled_cdev = lcdev_to_flcdev(led_cdev);
	u32 fault, mask = 0x1;
	char *pbuf = buf;
	int i, ret, buf_len;

	ret = led_get_flash_fault(fled_cdev, &fault);
	if (ret < 0)
		return -EINVAL;

	*buf = '\0';

	for (i = 0; i < LED_NUM_FLASH_FAULTS; ++i) {
		if (fault & mask) {
			buf_len = sprintf(pbuf, "%s ",
					  led_flash_fault_names[i]);
			pbuf += buf_len;
		}
		mask <<= 1;
	}

	return sprintf(buf, "%s\n", buf);
}
