parse_args(int argc, char **argv, int *old_optind, int *nargc, char ***nargv,
    struct sudo_settings **settingsp, char ***env_addp)
{
    struct environment extra_env;
    int mode = 0;
    int flags = 0;
    int valid_flags = DEFAULT_VALID_FLAGS;
    int ch, i;
    char *cp;
    const char *progname;
    int proglen;
    debug_decl(parse_args, SUDO_DEBUG_ARGS);


    if (argc <= 0)
	usage();


    progname = getprogname();
    sudo_settings[ARG_PROGNAME].value = progname;


    proglen = strlen(progname);
    if (proglen > 4 && strcmp(progname + proglen - 4, "edit") == 0) {
	progname = "sudoedit";
	mode = MODE_EDIT;
	sudo_settings[ARG_SUDOEDIT].value = "true";
	valid_flags = EDIT_VALID_FLAGS;
    }


    if (get_net_ifs(&cp) > 0)
	sudo_settings[ARG_NET_ADDRS].value = cp;


    i = sudo_conf_max_groups();
    if (i != -1) {
	if (asprintf(&cp, "%d", i) == -1)
	    sudo_fatalx(U_("%s: %s"), __func__, U_("unable to allocate memory"));
	sudo_settings[ARG_MAX_GROUPS].value = cp;
    }


#define got_host_flag	(optind > 1 && argv[optind - 1][0] == '-' && \
	    argv[optind - 1][1] == 'h' && argv[optind - 1][2] == '\0')


#define got_end_of_args	(optind > 1 && argv[optind - 1][0] == '-' && \
	    argv[optind - 1][1] == '-' && argv[optind - 1][2] == '\0')


#define is_envar (optind < argc && argv[optind][0] != '/' && \
	    strchr(argv[optind], '=') != NULL)


    memset(&extra_env, 0, sizeof(extra_env));


    for (;;) {


	if ((ch = getopt_long(argc, argv, short_opts, long_opts, NULL)) != -1) {
	    switch (ch) {
		case 'A':
		    SET(tgetpass_flags, TGP_ASKPASS);
		    break;
#ifdef HAVE_BSD_AUTH_H
		case 'a':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_BSDAUTH_TYPE].value != NULL)
			usage();
		    sudo_settings[ARG_BSDAUTH_TYPE].value = optarg;
		    break;
#endif
		case 'b':
		    SET(flags, MODE_BACKGROUND);
		    break;
		case 'B':
		    SET(tgetpass_flags, TGP_BELL);
		    break;
		case 'C':
		    assert(optarg != NULL);
		    if (sudo_strtonum(optarg, 3, INT_MAX, NULL) == 0) {
			sudo_warnx("%s",
			    U_("the argument to -C must be a number greater than or equal to 3"));
			usage();
		    }
		    if (sudo_settings[ARG_CLOSEFROM].value != NULL)
			usage();
		    sudo_settings[ARG_CLOSEFROM].value = optarg;
		    break;
#ifdef HAVE_LOGIN_CAP_H
		case 'c':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_LOGIN_CLASS].value != NULL)
			usage();
		    sudo_settings[ARG_LOGIN_CLASS].value = optarg;
		    break;
#endif
		case 'D':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_CWD].value != NULL)
			usage();
		    sudo_settings[ARG_CWD].value = optarg;
		    break;
		case 'E':


		    if (optarg == NULL) {
			sudo_settings[ARG_PRESERVE_ENVIRONMENT].value = "true";
			SET(flags, MODE_PRESERVE_ENV);
		    } else {
			parse_env_list(&extra_env, optarg);
		    }
		    break;
		case 'e':
		    if (mode && mode != MODE_EDIT)
			usage_excl();
		    mode = MODE_EDIT;
		    sudo_settings[ARG_SUDOEDIT].value = "true";
		    valid_flags = EDIT_VALID_FLAGS;
		    break;
		case 'g':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_RUNAS_GROUP].value != NULL)
			usage();
		    sudo_settings[ARG_RUNAS_GROUP].value = optarg;
		    break;
		case 'H':
		    sudo_settings[ARG_SET_HOME].value = "true";
		    SET(flags, MODE_RESET_HOME);
		    break;
		case 'h':
		    if (optarg == NULL) {


			if (got_host_flag && argv[optind] != NULL &&
			    argv[optind][0] != '-' && !is_envar) {
			    if (sudo_settings[ARG_REMOTE_HOST].value != NULL)
				usage();
			    sudo_settings[ARG_REMOTE_HOST].value = argv[optind++];
			    continue;
			}
			if (mode && mode != MODE_HELP) {
			    if (strcmp(progname, "sudoedit") != 0)
				usage_excl();
			}
			mode = MODE_HELP;
			valid_flags = 0;
			break;
		    }
		    FALLTHROUGH;
		case OPT_HOSTNAME:
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_REMOTE_HOST].value != NULL)
			usage();
		    sudo_settings[ARG_REMOTE_HOST].value = optarg;
		    break;
		case 'i':
		    sudo_settings[ARG_LOGIN_SHELL].value = "true";
		    SET(flags, MODE_LOGIN_SHELL);
		    break;
		case 'k':
		    sudo_settings[ARG_IGNORE_TICKET].value = "true";
		    break;
		case 'K':
		    sudo_settings[ARG_IGNORE_TICKET].value = "true";
		    if (mode && mode != MODE_KILL)
			usage_excl();
		    mode = MODE_KILL;
		    valid_flags = 0;
		    break;
		case 'l':
		    if (mode) {
			if (mode == MODE_LIST)
			    SET(flags, MODE_LONG_LIST);
			else
			    usage_excl();
		    }
		    mode = MODE_LIST;
		    valid_flags = LIST_VALID_FLAGS;
		    break;
		case 'n':
		    SET(flags, MODE_NONINTERACTIVE);
		    sudo_settings[ARG_NONINTERACTIVE].value = "true";
		    break;
		case 'P':
		    sudo_settings[ARG_PRESERVE_GROUPS].value = "true";
		    SET(flags, MODE_PRESERVE_GROUPS);
		    break;
		case 'p':

		    assert(optarg != NULL);
		    if (sudo_settings[ARG_PROMPT].value != NULL)
			usage();
		    sudo_settings[ARG_PROMPT].value = optarg;
		    break;
		case 'R':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_CHROOT].value != NULL)
			usage();
		    sudo_settings[ARG_CHROOT].value = optarg;
		    break;
#ifdef HAVE_SELINUX
		case 'r':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_SELINUX_ROLE].value != NULL)
			usage();
		    sudo_settings[ARG_SELINUX_ROLE].value = optarg;
		    break;
		case 't':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_SELINUX_TYPE].value != NULL)
			usage();
		    sudo_settings[ARG_SELINUX_TYPE].value = optarg;
		    break;
#endif
		case 'T':

		    assert(optarg != NULL);
		    if (sudo_settings[ARG_TIMEOUT].value != NULL)
			usage();
		    sudo_settings[ARG_TIMEOUT].value = optarg;
		    break;
		case 'S':
		    SET(tgetpass_flags, TGP_STDIN);
		    break;
		case 's':
		    sudo_settings[ARG_USER_SHELL].value = "true";
		    SET(flags, MODE_SHELL);
		    break;
		case 'U':
		    assert(optarg != NULL);
		    if (list_user != NULL || *optarg == '\0')
			usage();
		    list_user = optarg;
		    break;
		case 'u':
		    assert(optarg != NULL);
		    if (*optarg == '\0')
			usage();
		    if (sudo_settings[ARG_RUNAS_USER].value != NULL)
			usage();
		    sudo_settings[ARG_RUNAS_USER].value = optarg;
		    break;
		case 'v':
		    if (mode && mode != MODE_VALIDATE)
			usage_excl();
		    mode = MODE_VALIDATE;
		    valid_flags = VALIDATE_VALID_FLAGS;
		    break;
		case 'V':
		    if (mode && mode != MODE_VERSION)
			usage_excl();
		    mode = MODE_VERSION;
		    valid_flags = 0;
		    break;
		default:
		    usage();
	    }
	} else if (!got_end_of_args && is_envar) {

	    env_insert(&extra_env, argv[optind]);
	    optind++;
	} else {

	    break;
	}
    }

    argc -= optind;
    argv += optind;
    *old_optind = optind;

    if (!mode) {

	if (sudo_settings[ARG_IGNORE_TICKET].value != NULL) {
	    if (argc == 0 && !ISSET(flags, MODE_SHELL|MODE_LOGIN_SHELL)) {
		mode = MODE_INVALIDATE;
		sudo_settings[ARG_IGNORE_TICKET].value = NULL;
		valid_flags = 0;
	    }
	}
	if (!mode)
	    mode = MODE_RUN;
    }

    if (argc > 0 && mode == MODE_LIST)
	mode = MODE_CHECK;

    if (ISSET(flags, MODE_LOGIN_SHELL)) {
	if (ISSET(flags, MODE_SHELL)) {
	    sudo_warnx("%s",
		U_("you may not specify both the -i and -s options"));
	    usage();
	}
	if (ISSET(flags, MODE_PRESERVE_ENV)) {
	    sudo_warnx("%s",
		U_("you may not specify both the -i and -E options"));
	    usage();
	}
	SET(flags, MODE_SHELL);
    }
    if ((flags & valid_flags) != flags)
	usage();
    if (mode == MODE_EDIT &&
       (ISSET(flags, MODE_PRESERVE_ENV) || extra_env.env_len != 0)) {
	if (ISSET(mode, MODE_PRESERVE_ENV))
	    sudo_warnx("%s", U_("the -E option is not valid in edit mode"));
	if (extra_env.env_len != 0)
	    sudo_warnx("%s",
		U_("you may not specify environment variables in edit mode"));
	usage();
    }
    if ((sudo_settings[ARG_RUNAS_USER].value != NULL ||
	 sudo_settings[ARG_RUNAS_GROUP].value != NULL) &&
	!ISSET(mode, MODE_EDIT | MODE_RUN | MODE_CHECK | MODE_VALIDATE)) {
	usage();
    }
    if (list_user != NULL && mode != MODE_LIST && mode != MODE_CHECK) {
	sudo_warnx("%s",
	    U_("the -U option may only be used with the -l option"));
	usage();
    }
    if (ISSET(tgetpass_flags, TGP_STDIN) && ISSET(tgetpass_flags, TGP_ASKPASS)) {
	sudo_warnx("%s", U_("the -A and -S options may not be used together"));
	usage();
    }
    if ((argc == 0 && mode == MODE_EDIT) ||
	(argc > 0 && !ISSET(mode, MODE_RUN | MODE_EDIT | MODE_CHECK)))
	usage();
    if (argc == 0 && mode == MODE_RUN && !ISSET(flags, MODE_SHELL)) {
	SET(flags, (MODE_IMPLIED_SHELL | MODE_SHELL));
	sudo_settings[ARG_IMPLIED_SHELL].value = "true";
    }
#ifdef ENABLE_SUDO_PLUGIN_API
    sudo_settings[ARG_PLUGIN_DIR].value = sudo_conf_plugin_dir_path();
#endif

    if (mode == MODE_HELP)
	help();


    if (ISSET(flags, MODE_SHELL|MODE_LOGIN_SHELL) && ISSET(mode, MODE_RUN)) {
	char **av, *cmnd = NULL;
	int ac = 1;

	if (argc != 0) {

	    char *src, *dst;
	    size_t cmnd_size = (size_t) (argv[argc - 1] - argv[0]) +
		strlen(argv[argc - 1]) + 1;

	    cmnd = dst = reallocarray(NULL, cmnd_size, 2);
	    if (cmnd == NULL)
		sudo_fatalx(U_("%s: %s"), __func__, U_("unable to allocate memory"));
	    if (!gc_add(GC_PTR, cmnd))
		exit(EXIT_FAILURE);

	    for (av = argv; *av != NULL; av++) {
		for (src = *av; *src != '\0'; src++) {

		    if (!isalnum((unsigned char)*src) && *src != '_' && *src != '-' && *src != '$')
			*dst++ = '\\';
		    *dst++ = *src;
		}
		*dst++ = ' ';
	    }
	    if (cmnd != dst)
		dst--;
	    *dst = '\0';

	    ac += 2;
	}

	av = reallocarray(NULL, ac + 1, sizeof(char *));
	if (av == NULL)
	    sudo_fatalx(U_("%s: %s"), __func__, U_("unable to allocate memory"));
	if (!gc_add(GC_PTR, av))
	    exit(EXIT_FAILURE);

	av[0] = (char *)user_details.shell;
	if (cmnd != NULL) {
	    av[1] = "-c";
	    av[2] = cmnd;
	}
	av[ac] = NULL;

	argv = av;
	argc = ac;
    }


    if (mode == MODE_EDIT) {
#if defined(HAVE_SETRESUID) || defined(HAVE_SETREUID) || defined(HAVE_SETEUID)
	char **av;
	int ac;

	av = reallocarray(NULL, argc + 2, sizeof(char *));
	if (av == NULL)
	    sudo_fatalx(U_("%s: %s"), __func__, U_("unable to allocate memory"));
	if (!gc_add(GC_PTR, av))
	    exit(EXIT_FAILURE);


	av[0] = "sudoedit";
	for (ac = 0; argv[ac] != NULL; ac++) {
	    av[ac + 1] = argv[ac];
	}
	av[++ac] = NULL;

	argv = av;
	argc = ac;
#else
	sudo_fatalx("%s", U_("sudoedit is not supported on this platform"));
#endif
    }

    *settingsp = sudo_settings;
    *env_addp = extra_env.envp;
    *nargc = argc;
    *nargv = argv;
    debug_return_int(mode | flags);
}
