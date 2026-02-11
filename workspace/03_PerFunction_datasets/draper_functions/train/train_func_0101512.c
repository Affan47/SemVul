do_parse(json_config *config, const char *filename)
{
	FILE *input;
	json_parser parser;
	int ret;
	int col, lines;

	input = open_filename(filename, "r", 1);
	if (!input)
		return 2;


	ret = json_parser_init(&parser, config, NULL, NULL);
	if (ret) {
		fprintf(stderr, "error: initializing parser failed (code=%d): %s\n", ret, string_of_errors[ret]);
		return ret;
	}

	ret = process_file(&parser, input, &lines, &col);
	if (ret) {
		fprintf(stderr, "line %d, col %d: [code=%d] %s\n",
		        lines, col, ret, string_of_errors[ret]);
		return 1;
	}

	ret = json_parser_is_done(&parser);
	if (!ret) {
		fprintf(stderr, "syntax error\n");
		return 1;
	}

	close_filename(filename, input);
	return 0;
}
