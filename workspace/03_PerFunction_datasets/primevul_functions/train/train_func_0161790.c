main(int argc, char *argv[]) {
	int c, result = 0, specseen;
	char *options = NULL, *test_opts = NULL, *node;
	const char *spec = NULL;
	char *label = NULL;
	char *uuid = NULL;
	char *types = NULL;
	char *p;
	struct mntentchn *mc;
	int fd;

	sanitize_env();
	setlocale(LC_ALL, "");
	bindtextdomain(PACKAGE, LOCALEDIR);
	textdomain(PACKAGE);
	atexit(close_stdout);

	progname = argv[0];
	if ((p = strrchr(progname, '/')) != NULL)
		progname = p+1;

	umask(022);


	while((fd = open("/dev/null", O_RDWR)) == 0 || fd == 1 || fd == 2) ;
	if (fd > 2)
		close(fd);

	fsprobe_init();

#ifdef DO_PS_FIDDLING
	initproctitle(argc, argv);
#endif

	while ((c = getopt_long (argc, argv, "aBfFhilL:Mno:O:p:rRsU:vVwt:",
				 longopts, NULL)) != -1) {
		switch (c) {
		case 'a':
			++mount_all;
			break;
		case 'B':
			mounttype = MS_BIND;
			break;
		case 'f':
			++fake;
			break;
		case 'F':
			++optfork;
			break;
		case 'h':
			usage (stdout, 0);
			break;
		case 'i':
			external_allowed = 0;
			break;
		case 'l':
			list_with_volumelabel = 1;
			break;
		case 'L':
			label = optarg;
			break;
		case 'M':
			mounttype = MS_MOVE;
			break;
		case 'n':
			++nomtab;
			break;
		case 'o':
			options = append_opt(options, optarg, NULL);
			break;
		case 'O':
			test_opts = append_opt(test_opts, optarg, NULL);
			break;
		case 'p':
                        error("mount: %s", _("--pass-fd is no longer supported"));
			break;
		case 'r':
			readonly = 1;
			readwrite = 0;
			break;
		case 'R':
			mounttype = (MS_BIND | MS_REC);
			break;
		case 's':
			sloppy = 1;
			break;
		case 't':
			types = optarg;
			break;
		case 'U':
			uuid = optarg;
			break;
		case 'v':
			++verbose;
			break;
		case 'V':
			print_version(EXIT_SUCCESS);
			break;
		case 'w':
			readwrite = 1;
			readonly = 0;
			break;
		case 0:
			break;

		case 136:
			mounttype = MS_SHARED;
			break;

		case 137:
			mounttype = MS_SLAVE;
			break;

		case 138:
			mounttype = MS_PRIVATE;
			break;

		case 139:
			mounttype = MS_UNBINDABLE;
			break;

		case 140:
			mounttype = (MS_SHARED | MS_REC);
			break;

		case 141:
			mounttype = (MS_SLAVE | MS_REC);
			break;

		case 142:
			mounttype = (MS_PRIVATE | MS_REC);
			break;

		case 143:
			mounttype = (MS_UNBINDABLE | MS_REC);
			break;
		case 144:
			nocanonicalize = 1;
			break;
		case '?':
		default:
			usage (stderr, EX_USAGE);
		}
	}

	if (verbose > 2) {
		printf("mount: fstab path: \"%s\"\n", _PATH_MNTTAB);
		printf("mount: mtab path:  \"%s\"\n", _PATH_MOUNTED);
		printf("mount: lock path:  \"%s\"\n", _PATH_MOUNTED_LOCK);
		printf("mount: temp path:  \"%s\"\n", _PATH_MOUNTED_TMP);
		printf("mount: UID:        %u\n", getuid());
		printf("mount: eUID:       %u\n", geteuid());
	}

	argc -= optind;
	argv += optind;

	specseen = (uuid || label) ? 1 : 0;

	if (argc+specseen == 0 && !mount_all) {
		if (options || mounttype)
			usage (stderr, EX_USAGE);
		return print_all (types);
	}

	{
		const uid_t ruid = getuid();
		const uid_t euid = geteuid();


		if (((uid_t)0 == ruid) && (ruid == euid)) {
			restricted = 0;
		}

		if (restricted &&
		    (types || options || readwrite || nomtab || mount_all ||
		     nocanonicalize || fake || mounttype ||
		     (argc + specseen) != 1)) {

			if (ruid == 0 && euid != 0)

				die (EX_USAGE, _("mount: only root can do that "
					"(effective UID is %u)"), euid);

			die (EX_USAGE, _("mount: only root can do that"));
		}
	}

	atexit(unlock_mtab);

	switch (argc+specseen) {
	case 0:

		result = do_mount_all (types, options, test_opts);
		if (result == 0 && verbose && !fake)
			error(_("nothing was mounted"));
		break;

	case 1:


		if (types != NULL)
			usage (stderr, EX_USAGE);

		if (uuid || label)
			mc = getfs(NULL, uuid, label);
		else
			mc = getfs(*argv, NULL, NULL);

		if (!mc) {
			if (uuid || label)
				die (EX_USAGE, _("mount: no such partition found"));

			die (EX_USAGE,
			     _("mount: can't find %s in %s or %s"),
			     *argv, _PATH_MNTTAB, _PATH_MOUNTED);
		}

		result = mount_one (xstrdup (mc->m.mnt_fsname),
				    xstrdup (mc->m.mnt_dir),
				    xstrdup (mc->m.mnt_type),
				    mc->m.mnt_opts, options, 0, 0);
		break;

	case 2:

		if (specseen) {

			spec = uuid ?	fsprobe_get_devname_by_uuid(uuid) :
					fsprobe_get_devname_by_label(label);
			node = argv[0];
		} else {

			spec = argv[0];
			node = argv[1];
		}
		if (!spec)
			die (EX_USAGE, _("mount: no such partition found"));

		result = mount_one (spec, node, types, NULL, options, 0, 0);
		break;

	default:
		usage (stderr, EX_USAGE);
	}

	if (result == EX_SOMEOK)
		result = 0;

	fsprobe_exit();

	exit (result);
}
