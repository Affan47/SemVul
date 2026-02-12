getToken(FileInfo *file, CharsString *result, const char *description) {


	while (!atEndOfLine(file) && atTokenDelimiter(file)) file->linepos++;
	result->length = 0;
	while (!atEndOfLine(file) && !atTokenDelimiter(file)) {
		int maxlen = MAXSTRING;
		if (result->length >= maxlen) {
			compileError(file, "more than %d characters (bytes)", maxlen);
			return 0;
		} else
			result->chars[result->length++] = file->line[file->linepos++];
	}
	if (!result->length) {

		if (description) compileError(file, "%s not specified.", description);
		return 0;
	}
	result->chars[result->length] = 0;
	while (!atEndOfLine(file) && atTokenDelimiter(file)) file->linepos++;
	return 1;
}
