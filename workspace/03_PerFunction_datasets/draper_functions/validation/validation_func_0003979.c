detect_byteblaster(int device)
{
	if (debug)
		printf("Detecting byteblaster\n");


	if (debug)
		printf("Driving D5 low\n");
	set_D5(device, 0);
	usleep(10000);
	if (get_ACK(device) == 1)
	{
		if (debug)
			fprintf(stderr, "ACK stuck high\n");
		return -1;
	}

	if (debug)
		printf("Driving D5 high\n");
	set_D5(device, 1);
	usleep(10000);
	if (get_ACK(device) == 0)
	{
		if (debug)
			fprintf(stderr, "ACK stuck low\n");
		return -1;
	}

	if (debug)
		printf("Driving D5 low\n");
	set_D5(device, 0);
	usleep(10000);
	if (get_ACK(device) == 1)
	{
		if (debug)
			fprintf(stderr, "ACK stuck high\n");
		return -1;
	}

	return 0;
}
