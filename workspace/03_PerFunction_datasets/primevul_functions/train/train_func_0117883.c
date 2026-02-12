main (int argc, char *argv[]) {
	int c;
	int all = 0;
	char *types = NULL, *test_opts = NULL, *p;
	int result = 0;

	sanitize_env();
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);

	progname = argv[0];
	if ((p = strrchr(progname, '/')) != NULL)
		progname = p+1;

	umask(022);

	while ((c = getopt_long (argc, argv, "adfhlnrit:O:vV",
				 longopts, NULL)) != -1)
		switch (c) {
		case 'a':
			++all;
			break;

		case 'd':
			++delloop;
			break;
		case 'f':
			++force;
			break;
		case 'h':
			usage (stdout, 0);
			break;
		case 'l':
			++lazy;
			break;
		case 'n':
			++nomtab;
			break;
		case 'O':
			test_opts = optarg;
			break;
		case 'r':
			++remount;
			break;
		case 'v':
			++verbose;
			break;
		case 'V':
			printf ("umount (%s)\n", PACKAGE_STRING);
			exit (0);
		case 't':
			types = optarg;
			break;
		case 'i':
			external_allowed = 0;
			break;
		case 144:
			nocanonicalize = 1;
			break;
		case 145:
			fake = 1;
			break;
		case 0:
			break;
		case '?':
		default:
			usage (stderr, 1);
		}

	{
		const uid_t ruid = getuid();
		const uid_t euid = geteuid();


		if (((uid_t)0 == ruid) && (ruid == euid)) {
			restricted = 0;
		}
	}

	if (restricted &&
	    (all || types || nomtab || force || remount || nocanonicalize ||
	     fake)) {
		die (2, _("umount: only root can do that"));
	}

	argc -= optind;
	argv += optind;

	atexit(unlock_mtab);

#ifdef HAVE_LIBMOUNT_MOUNT
	mnt_init_debug(0);
#endif
	if (all) {

		if (types == NULL)
			types = "noproc,nodevfs,nodevpts,nosysfs,norpc_pipefs,nonfsd";
		result = umount_all (types, test_opts);
	} else if (argc < 1) {
		usage (stderr, 2);
	} else while (argc--) {
		result += umount_file(*argv++);
	}
	exit (result);
}
