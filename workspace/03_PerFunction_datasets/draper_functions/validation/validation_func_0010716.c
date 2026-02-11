whole_string_match_regex(const char *text, char *pattern)
{
	char *new_pattern;
	int result;

	if(!pattern || !text)
		return 0;

	new_pattern = (char *) malloc(sizeof(char) * (strlen(pattern) + 3));
	if(!new_pattern)
		return 0;

	new_pattern[0] = '\0';
	if(*pattern != '^')
		strncat(new_pattern, "^", 1);
	strncat(new_pattern, pattern, strlen(pattern));
	if(text[strlen(pattern) - 1] != '$')
		strncat(new_pattern, "$", 1);

	result = string_match_regex(text, new_pattern);
	free(new_pattern);

	return result;
}
