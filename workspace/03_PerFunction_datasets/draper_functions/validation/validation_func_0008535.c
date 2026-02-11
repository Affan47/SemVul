serio_set_bind_mode(struct device *dev, struct device_attribute *attr, const char *buf, size_t count)
{
	struct serio *serio = to_serio_port(dev);
	int retval;

	retval = count;
	if (!strncmp(buf, "manual", count)) {
		serio->manual_bind = true;
	} else if (!strncmp(buf, "auto", count)) {
		serio->manual_bind = false;
	} else {
		retval = -EINVAL;
	}

	return retval;
}
