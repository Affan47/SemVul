getfs(const char *spec, const char *uuid, const char *label)
{
	struct mntentchn *mc = NULL;
	const char *devname = NULL;

	if (!spec && !uuid && !label)
		return NULL;


	if (uuid)
		mc = getfs_by_uuid(uuid);
	else if (label)
		mc = getfs_by_label(label);
	else {
		mc = getfs_by_dir(spec);

		if (!mc)
			mc = getfs_by_spec(spec);
	}
	if (mc)
		return mc;


	if (uuid)
		devname = fsprobe_get_devname_by_uuid(uuid);
	else if (label)
		devname = fsprobe_get_devname_by_label(label);
	else
		devname = spec_to_devname(spec);

	if (devname)
		mc = getfs_by_devname(devname);


	if (!mc && devname) {
		const char *id = NULL;

		if (!label && (!spec || strncmp(spec, "LABEL=", 6))) {
			id = fsprobe_get_label_by_devname(devname);
			if (id)
				mc = getfs_by_label(id);
		}
		if (!mc && !uuid && (!spec || strncmp(spec, "UUID=", 5))) {
			id = fsprobe_get_uuid_by_devname(devname);
			if (id)
				mc = getfs_by_uuid(id);
		}
		my_free(id);

		if (mc) {


			my_free(mc->m.mnt_fsname);
			mc->m.mnt_fsname = xstrdup(devname);
		}
	}


	if (!mc && (devname || spec))
		mc = getmntfilebackward (devname ? devname : spec, NULL);

	my_free(devname);
	return mc;
}
