recover_mode(const char *arg, struct termios *mode)
{
	int i, n;
	unsigned chr;
	unsigned long iflag, oflag, cflag, lflag;


	if (sscanf(arg, "%lx:%lx:%lx:%lx%n",
			   &iflag, &oflag, &cflag, &lflag, &n) != 4)
		return 0;
	mode->c_iflag = iflag;
	mode->c_oflag = oflag;
	mode->c_cflag = cflag;
	mode->c_lflag = lflag;
	arg += n;
	for (i = 0; i < NCCS; ++i) {
		if (sscanf(arg, ":%x%n", &chr, &n) != 1)
			return 0;
		mode->c_cc[i] = chr;
		arg += n;
	}


	if (*arg != '\0')
		return 0;

	return 1;
}
