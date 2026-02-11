main(int argc, char *argv[])
{
    const char *book_directory;
    ssize_t max_text_length;
    const char *subbook_name;
    int show_stop_code_flag;
    EB_Position text_position;
    unsigned int stop_code0, stop_code1;
    int ch;

    invoked_name = argv[0];
    max_text_length = DEFAULT_MAX_TEXT_LENGTH;
    show_stop_code_flag = 1;
    stop_code0 = DUMMY_STOP_CODE0;
    stop_code1 = DUMMY_STOP_CODE1;
    text_position.page = 0;
    text_position.offset = 0;


#ifdef ENABLE_NLS
#ifdef HAVE_SETLOCALE
       setlocale(LC_ALL, "");
#endif
       bindtextdomain(TEXT_DOMAIN_NAME, LOCALEDIR);
       textdomain(TEXT_DOMAIN_NAME);
#endif


    for (;;) {
	ch = getopt_long(argc, argv, short_options, long_options, NULL);
	if (ch == -1)
	    break;

	switch (ch) {
        case 'c':


	    if (parse_stop_code_argument(optarg, &stop_code0, &stop_code1) < 0)
		goto die;
	    max_text_length = 0;
            break;

	case 'h':


	    output_help();
	    exit(0);

        case 'l':


	    if (parse_text_length_argument(optarg, &max_text_length) < 0)
		goto die;
	    stop_code0 = DUMMY_STOP_CODE0;
	    stop_code1 = DUMMY_STOP_CODE1;
            break;

	case 'n':


	    show_stop_code_flag = 0;
	    break;

	case 'p':


	    if (parse_text_position_argument(optarg, &text_position) < 0)
		goto die;
	    break;

	case 'v':


	    output_version(program_name, program_version);
	    exit(0);

	default:
	    output_try_help(invoked_name);
	    goto die;
	}
    }


    if (argc - optind < 2) {
	fprintf(stderr, _("%s: too few argument\n"), invoked_name);
	output_try_help(invoked_name);
	goto die;
    }
    if (2 < argc - optind) {
	fprintf(stderr, _("%s: too many arguments\n"), invoked_name);
	output_try_help(invoked_name);
	goto die;
    }
    if (argc - optind == 2) {
	book_directory = argv[optind];
	subbook_name = argv[optind + 1];
    } else {
	book_directory = DEFAULT_BOOK_DIRECTORY;
	subbook_name = argv[optind];
    }


    if (scan_subbook_text(book_directory, subbook_name, &text_position,
	max_text_length, show_stop_code_flag, stop_code0, stop_code1) < 0)
	goto die;

    return 0;

  die:
    fflush(stdout);
    exit(1);
}
