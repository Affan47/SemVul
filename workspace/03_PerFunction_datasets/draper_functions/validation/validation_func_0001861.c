get_arguments(int argc, char **argv)
{
	const char *dir;
	int opt;
	#if HAVE_GETOPT_LONG
	int index = 0;
	#endif

	for(;;)
	{
		#if HAVE_GETOPT_LONG
			opt = getopt_long(argc, argv, "gvaVhLtpmser:", Long_options, &index);
		#else
			opt = getopt(argc, argv, "gvaVhLtpmser:");
		#endif
		if (opt < 0) break;

		switch (opt)
		{
			case 'V':
				printf(VERSION "\n");
				exit(0);

			case 'g':
				main_debug = TRUE;
				break;

			case 'v':
				main_verbose = TRUE;
				break;

			case 'a':
				main_compile_all = TRUE;
				break;

			case 't':
				main_trans = TRUE;
				break;

			case 'p':
				main_public = TRUE;
				break;

			case 'm':
				main_public_module = TRUE;
				break;

			case 's':
				main_swap = TRUE;
				break;


			case 'r':
				COMP_root = STR_copy(optarg);
				break;

			case 'e':
				ERROR_translate = TRUE;
				break;

			case 1:
				main_no_old_read_syntax = TRUE;
				break;

			case 'L':
				printf(
					"GAMBAS Compiler version " VERSION " " __DATE__ " " __TIME__ "\n"
					COPYRIGHT
					);
				exit(0);

			case 'h': case '?':
				printf(
					"Usage: gbc" GAMBAS_VERSION_STRING " [options] [<project directory>]\n\n"
					"Options:"
					#if HAVE_GETOPT_LONG
					"\n"
					"  -g  --debug                add debugging information\n"
					"  -v  --verbose              verbose output\n"
					"  -a  --all                  compile all\n"
					"  -t  --translate            output translation files\n"
					"  -p  --public-control       form controls are public\n"
					"  -m  --public-module        module symbols are public by default\n"
					"  -s  --swap                 swap endianness\n"
					"  -r  --root <directory>     gives the gambas installation directory\n"
					"  -V  --version              display version\n"
					"  -h  --help                 display this help\n"
					"  -L  --license              display license\n"
					"  -e  --translate-errors     display translatable error messages\n"
					#else
					" (no long options on this system)\n"
					"  -g                         add debugging information\n"
					"  -v                         verbose output\n"
					"  -a                         compile all\n"
					"  -t                         output translation files\n"
					"  -p                         form controls are public\n"
					"  -m                         module symbols are public by default\n"
					"  -s                         swap endianness\n"
					"  -r <directory>             gives the gambas installation directory\n"
					"  -V                         display version\n"
					"  -h                         display this help\n"
					"  -L                         display license\n"
					"  -e                         display translatable error messages\n"
					#endif
					"\n"
					);

				exit(0);

			default:
				exit(1);

		}
	}

	if (optind < (argc - 1))
	{
		fprintf(stderr, "gbc: too many arguments.\n");
		exit(1);
	}


	if (optind < argc)
		FILE_chdir(argv[optind]);

	dir = FILE_get_current_dir();
	if (!dir)
	{
		fprintf(stderr, "gbc: no current directory.\n");
		exit(1);
	}

	COMP_project = STR_copy(FILE_cat(dir, ".project", NULL));

	if (!FILE_exist(COMP_project))
	{
		fprintf(stderr, "gbc: project file not found: %s\n", COMP_project);
		exit(1);
	}
}
