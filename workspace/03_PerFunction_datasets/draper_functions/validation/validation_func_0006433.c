handle_args (int argc, char ** argv)
{
    int c;
    char * s;

    while ((c = getopt (argc, argv, "hs:t:T")) != -1)
	switch (c) {
	case 's':
	    demux_track = strtol (optarg, &s, 0);
	    if (demux_track < 0x80)
		demux_track += 0x80;
	    if (demux_track < 0x80 || demux_track > 0x87 || *s) {
		fprintf (stderr, "Invalid track number: %s\n", optarg);
		print_usage (argv);
	    }
	    break;

	case 't':
	    demux_pid = strtol (optarg, &s, 0);
	    if (demux_pid < 0x10 || demux_pid > 0x1ffe || *s) {
		fprintf (stderr, "Invalid pid: %s\n", optarg);
		print_usage (argv);
	    }
	    break;

	case 'T':
	    demux_pes = 1;
	    break;

	default:
	    print_usage (argv);
	}

    if (optind < argc) {
	in_file = fopen (argv[optind], "rb");
	if (!in_file) {
	    fprintf (stderr, "%s - could not open file %s\n", strerror (errno),
		     argv[optind]);
	    exit (1);
	}
    } else
	in_file = stdin;
}
