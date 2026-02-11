setconsole_main(int argc UNUSED_PARAM, char **argv)
{
	const char *device = CURRENT_TTY;
	bool reset;

#if ENABLE_FEATURE_SETCONSOLE_LONG_OPTIONS
	static const char setconsole_longopts[] ALIGN1 =
		"reset\0" No_argument "r"
		;
	applet_long_options = setconsole_longopts;
#endif

	opt_complementary = "?1";
	reset = getopt32(argv, "r");

	argv += 1 + reset;
	if (*argv) {
		device = *argv;
	} else {
		if (reset)
			device = DEV_CONSOLE;
	}

	xioctl(xopen(device, O_RDONLY), TIOCCONS, NULL);
	return EXIT_SUCCESS;
}
