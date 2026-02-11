optProc( int argc, char *const *argv, int opt )
{
    switch (opt) {
    case 'C':
        while (*optarg) {
            switch (*optarg++) {
		case 'a':
			aflag = 1;
			break;
		case 'b':
			bflag = 1;
			break;
		case 'd':
			dflag = 1;
			break;
		case 'f':
                        if (!*optarg)
                            optarg = argv[optind++];
			if (strcmp(optarg, "inet") == 0)
				af = AF_INET;
			else if (strcmp(optarg, "inet6") == 0)
				af = AF_INET6;


			else {
				(void)fprintf(stderr,
				    "%s: %s: unknown address family\n",
				    progname, optarg);
				exit(1);
			}
			return;
		case 'g':
			gflag = 1;
			break;
		case 'I':
			iflag = 1;
                        if (!*optarg)
                            optarg = argv[optind++];
			intrface = optarg;
			return;
		case 'i':
			iflag = 1;
			break;
		case 'L':
			Lflag = 1;
			break;


		case 'm':
			mflag = 1;
			break;


		case 'n':
			nflag = 1;
			break;
		case 'o':
			oflag = 1;
			break;


		case 'p':
                        if (!*optarg)
                            optarg = argv[optind++];
			if ((tp = name2protox(optarg)) == NULL) {
				(void)fprintf(stderr,
				    "%s: %s: unknown protocol\n",
				    progname, optarg);
				exit(1);
			}
			pflag = 1;
			return;


		case 'r':
			rflag = 1;
			break;
		case 'R':
                        if (optind < argc) {
                            if (argv[optind]) {
                                max_getbulk = atoi(argv[optind]);
                                if (max_getbulk == 0) {
                                    usage();
                                    fprintf(stderr, "Bad -CR option: %s\n",
                                            argv[optind]);
                                    exit(1);
                                }
                            }
                        } else {
                            usage();
                            fprintf(stderr, "Bad -CR option: no argument given\n");
                            exit(1);
                        }
                        optind++;
                        break;
		case 'S':


			Sflag = 1;
			break;
		case 's':
			++sflag;
			break;


		case 'v':
			vflag = 1;
			break;
		case 'w':
                        if (!*optarg)
                            optarg = argv[optind++];
			interval = atoi(optarg);
			iflag = 1;
			return;
		case '?':
		default:
			usage();
            }
        }
        break;


    case 'i':
	iflag = 1;
	break;
    case 'R':
	rflag = 1;
	break;
    case 's':
	++sflag;
	break;
    }
}
