killswitch_new (GUdevDevice *device, RfKillType rtype)
{
	Killswitch *ks;
	GUdevDevice *parent = NULL, *grandparent = NULL;
	const char *driver, *subsys, *parent_subsys = NULL;

	ks = g_malloc0 (sizeof (Killswitch));
	ks->name = g_strdup (g_udev_device_get_name (device));
	ks->seqnum = g_udev_device_get_seqnum (device);
	ks->path = g_strdup (g_udev_device_get_sysfs_path (device));
	ks->rtype = rtype;

	driver = g_udev_device_get_property (device, "DRIVER");
	subsys = g_udev_device_get_subsystem (device);


	parent = g_udev_device_get_parent (device);
	if (parent) {
		parent_subsys = g_udev_device_get_subsystem (parent);
		if (!driver)
			driver = g_udev_device_get_property (parent, "DRIVER");
		if (!driver) {

			grandparent = g_udev_device_get_parent (parent);
			if (grandparent)
				driver = g_udev_device_get_property (grandparent, "DRIVER");
		}
	}

	if (!driver)
		driver = "(unknown)";
	ks->driver = g_strdup (driver);

	if (   g_strcmp0 (subsys, "platform") == 0
	    || g_strcmp0 (parent_subsys, "platform") == 0
	    || g_strcmp0 (subsys, "acpi") == 0
	    || g_strcmp0 (parent_subsys, "acpi") == 0)
		ks->platform = TRUE;

	if (grandparent)
		g_object_unref (grandparent);
	if (parent)
		g_object_unref (parent);
	return ks;
}
