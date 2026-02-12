getToken(FileInfo *nested, CharsString *result, const char *description, int *lastToken) {


	while (!atEndOfLine(nested) && atTokenDelimiter(nested)) nested->linepos++;
	result->length = 0;
	while (!atEndOfLine(nested) && !atTokenDelimiter(nested)) {
		int maxlen = MAXSTRING;
		if (result->length >= maxlen) {
			compileError(nested, "more than %d characters (bytes)", maxlen);
			return 0;
		} else
			result->chars[result->length++] = nested->line[nested->linepos++];
	}
	if (!result->length) {

		if (description) compileError(nested, "%s not specified.", description);
		return 0;
	}
	result->chars[result->length] = 0;
	while (!atEndOfLine(nested) && atTokenDelimiter(nested)) nested->linepos++;
	return (*lastToken = atEndOfLine(nested)) ? 2 : 1;
}
