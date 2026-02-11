set_mask(const struct evemu_device *dev, int type, int fd)
{
	int bits = 8 * dev->mbytes[type];
	int ret, i;
	for (i = 0; i < bits; i++) {
		if (!evemu_has_event(dev, type, i))
			continue;


		if (type == EV_ABS &&
			evemu_get_abs_maximum(dev, i) == 0 && evemu_get_abs_minimum(dev, i) == 0)
			continue;

		ret = set_event_bit(fd, type, i);
		if (ret < 0)
			return ret;
	}
	return 0;
}
