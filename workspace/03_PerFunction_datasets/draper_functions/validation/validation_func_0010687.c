ide_read_setting(ide_drive_t *drive,
			    const struct ide_proc_devset *setting)
{
	const struct ide_devset *ds = setting->setting;
	int val = -EINVAL;

	if (ds->get)
		val = ds->get(drive);

	return val;
}
