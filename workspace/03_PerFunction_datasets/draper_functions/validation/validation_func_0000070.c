kempld_get_info(struct kempld_device_data *pld)
{
	int ret;
	struct kempld_platform_data *pdata = dev_get_platdata(pld->dev);
	char major, minor;

	ret = pdata->get_info(pld);
	if (ret)
		return ret;


	if (pld->info.major < 10)
		major = pld->info.major + '0';
	else
		major = (pld->info.major - 10) + 'A';
	if (pld->info.minor < 10)
		minor = pld->info.minor + '0';
	else
		minor = (pld->info.minor - 10) + 'A';

	ret = scnprintf(pld->info.version, sizeof(pld->info.version),
			"P%X%c%c.%04X", pld->info.number, major, minor,
			pld->info.buildnr);
	if (ret < 0)
		return ret;

	return 0;
}
