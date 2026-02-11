lha_reader_new(LHAInputStream *stream)
{
	LHABasicReader *basic_reader;
	LHAReader *reader;

	basic_reader = lha_basic_reader_new(stream);

	if (basic_reader == NULL) {
		return NULL;
	}

	reader = malloc(sizeof(LHAReader));

	if (reader == NULL) {
		lha_basic_reader_free(basic_reader);
		return NULL;
	}

	reader->reader = basic_reader;
	reader->curr_file = NULL;
	reader->curr_file_type = CURR_FILE_START;
	reader->decoder = NULL;
	reader->inner_decoder = NULL;
	reader->dir_stack = NULL;
	reader->dir_policy = LHA_READER_DIR_END_OF_DIR;

	return reader;
}
