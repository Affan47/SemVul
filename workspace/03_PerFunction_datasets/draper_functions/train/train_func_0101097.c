main(int argc, char **argv)
{
    FILE *instream;
    char *err = NULL;
    sieve_script_t *s;
    bytecode_info_t *bc;
    int c, fd, usage_error = 0;
    char *alt_config = NULL;

    while ((c = getopt(argc, argv, "C:")) != EOF)
	switch (c) {
	case 'C':
	    alt_config = optarg;
	    break;
	default:
	    usage_error = 1;
	    break;
	}

    if (usage_error || (argc - optind) < 2) {
	fprintf(stderr, "Syntax: %s [-C <altconfig>] <filename> <outputfile>\n",
	       argv[0]);
	exit(1);
    }

    instream = fopen(argv[optind++],"r");
    if(instream == NULL) {
	fprintf(stderr, "Unable to open %s for reading\n", argv[1]);
	exit(1);
    }


    config_read(alt_config);

    if(is_script_parsable(instream, &err, &s) == TIMSIEVE_FAIL) {
	if(err) {
	    fprintf(stderr, "Unable to parse script: %s\n", err);
	} else {
	    fprintf(stderr, "Unable to parse script.\n");
	}

	exit(1);
    }


    if(sieve_generate_bytecode(&bc, s) == -1) {
	fprintf(stderr, "bytecode generate failed\n");
	exit(1);
    }


    fd = open(argv[optind], O_CREAT | O_TRUNC | O_WRONLY, 0644);
    if(fd < 0) {
	fprintf(stderr, "couldn't open bytecode output file\n");
	exit(1);
    }


    if(sieve_emit_bytecode(fd, bc) == -1) {
	fprintf(stderr, "bytecode emit failed\n");
	exit(1);
    }

    close(fd);

    sieve_free_bytecode(&bc);
    sieve_script_free(&s);

    return 0;
}
