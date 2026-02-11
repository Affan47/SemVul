found_device_new(const bdaddr_t *bdaddr,
					uint8_t bdaddr_type, const char *name,
					const char *alias, uint32_t class,
					gboolean legacy, int flags)
{
	struct remote_dev_info *dev;

	dev = g_new0(struct remote_dev_info, 1);
	bacpy(&dev->bdaddr, bdaddr);
	dev->bdaddr_type = bdaddr_type;
	dev->name = g_strdup(name);
	dev->alias = g_strdup(alias);
	dev->class = class;
	dev->legacy = legacy;
	if (flags >= 0)
		dev->flags = flags;

	return dev;
}
