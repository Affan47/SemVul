umount_all2(char *devs[], int flags)
{
	int i;
	int ret;

	for (i = 0; devs[i]; i++)
	{
		ret = umount_main(devs[i], flags);
		if (ret < 0)
		{
			return ret;
		}
	}

	return 0;
}
