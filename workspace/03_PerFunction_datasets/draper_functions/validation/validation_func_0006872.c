main(int argc, char **argv)
{
	char *device = "/dev/video0";
	unsigned cnt = 0;
	int fh;
	time_t t;

	double f[2] = { 147.25, 154.25 };

	if (argc > 1) device = argv[1];

	fh = open(device, O_RDONLY);

	if (fh == -1) {
		fprintf(stderr, "cannot open %s\n", device);
		return -1;
	}
	for (;;) {
		struct v4l2_frequency vf;
		int err;

		cnt++;
		vf.tuner = 0;
		vf.type = V4L2_TUNER_ANALOG_TV;
		vf.frequency = f[cnt % 2] * 16;
		t = time(NULL);
		printf("%06u: %.2f %s", cnt, f[cnt % 2], ctime(&t));
		if ((err = ioctl(fh, VIDIOC_S_FREQUENCY, &vf))) {
			perror("could not set frequency");
			return -1;
		}
	}

	return 0;
}
