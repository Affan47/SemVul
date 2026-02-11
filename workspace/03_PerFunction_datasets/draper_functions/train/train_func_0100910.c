main(int argc, char **argv) {
	int opt;
	int i;


	while ((opt = getopt(argc, argv, "dO:phs:")) >= 0) {
		switch (opt) {
			case 'd': debug = 1; break;
			case 'O': optimized = 1; resched_buf_len = atoi(optarg); break;
			case 'p': profile = 1; break;
			case 'h': help(); return 0;
			case 's': stall_range = atoi(optarg); break;
			default: help(); return 1;
		}
	}
	if (optind < argc) {
		debug_msg("Read from %s.\n", argv[optind]);
		yyin = fopen(argv[optind], "r");
		if (!yyin) die();
	}
	else
		yyin = stdin;

	debug_msg("Parse assembly code.\n");
	if (yyparse() > 0) { printf("Syntax error\n"); exit(1); }
	debug_msg("%d instruction(s) has been loaded.\n", n_ins);
	if (debug) {
		for (i = 0; i < n_ins; i++) {
			print_ins(&ins_buf[i]);
			printf("\n");
		}
	}

	debug_msg("Start exectuion. Reschedule-buffer: %d.\n", resched_buf_len);
	run();

	return 0;
}
