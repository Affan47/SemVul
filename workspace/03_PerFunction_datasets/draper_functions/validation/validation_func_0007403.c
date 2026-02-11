sw_keypad()
{
	fd = open("/dev/tty", O_RDONLY);
	if (fd < 0) {
		printf("*** open error %d\n", errno);
		return (R_ERR);
	}
	if (tcgetattr(fd, &terma) < 0) {
		printf("*** tcgetattr error %d\n", errno);
		return (R_ERR);
	}
	tcgetattr(fd, &termb);
	termb.c_lflag &= ~(ICANON | ECHO);
	termb.c_cc[VMIN] = 1;
	termb.c_cc[VTIME] = 0;
	if (tcsetattr(fd, TCSADRAIN, &termb) < 0) {
		printf("*** tcsetattr error %d\n", errno);
		return (R_ERR);
	}
	return (R_OK);
}
