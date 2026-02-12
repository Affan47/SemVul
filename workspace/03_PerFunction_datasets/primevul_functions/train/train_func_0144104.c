main(int argc, char **argv) {
	int optc;

	set_program_name(argv[0]);

	while ((optc = getopt_long(argc, argv, "hvfb", longopts, NULL)) != -1) {
		switch (optc) {

		case 'v':
			version_etc(
					stdout, program_name, PACKAGE_NAME, VERSION, AUTHORS, (char *)NULL);
			exit(EXIT_SUCCESS);
			break;
		case 'h':
			print_help();
			exit(EXIT_SUCCESS);
			break;
		case 'f':
			forward_flag = 1;
			break;
		case 'b':
			backward_flag = 1;
			break;
		default:
			fprintf(stderr, "Try `%s --help' for more information.\n", program_name);
			exit(EXIT_FAILURE);
			break;
		}
	}

	if (forward_flag && backward_flag) {
		fprintf(stderr, "%s: specify either -f or -b but not both\n", program_name);
		fprintf(stderr, "Try `%s --help' for more information.\n", program_name);
		exit(EXIT_FAILURE);
	}


	if (!argv[optind + 0]) {
		fprintf(stderr, "%s: no table specified\n", program_name);
		fprintf(stderr, "Try `%s --help' for more information.\n", program_name);
		exit(EXIT_FAILURE);
	}
	if (argv[optind + 1]) {
		input = fopen(argv[optind + 1], "r");
	} else
		input = stdin;


	translate_input(!backward_flag, argv[optind]);
	exit(EXIT_SUCCESS);
}
