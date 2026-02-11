open_byteblaster(char *devicename)
{
	int dev;

	dev = open_parport(devicename);
	if (dev < 0 )
	{
		if (!quiet)
			fprintf(stderr, "Can't open %s!\n", devicename);
		return -1;
	}

	if (detect_byteblaster(dev) < 0)
	{
		if (!quiet)
			fprintf(stderr, "Byteblaster not found on %s!\n", devicename);
		close_byteblaster(dev);
		return -1;
	}

	return dev;
}
