preparse_args(int argc, char **argv) {
	char *option;

	for (argc--, argv++; argc > 0; argc--, argv++) {
		if (argv[0][0] != '-')
			continue;
		option = &argv[0][1];
		while (strpbrk(option, single_dash_opts) == &option[0]) {
			if (option[0] == 'm') {
				isc_mem_debugging = ISC_MEM_DEBUGTRACE |
					ISC_MEM_DEBUGRECORD;
				return;
			}
			option = &option[1];
		}
	}
}
