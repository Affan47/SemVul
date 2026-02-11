gfarm_pattern_charset_parse(const char *pattern, int index, int *ip)
{
	int i = index;

	if (pattern[i] == '!')
		i++;
	if (pattern[i] != '\0') {
		if (pattern[i + 1] == '-' && pattern[i + 2] != '\0')
			i += 3;
		else
			i++;
	}
	while (pattern[i] != ']') {
		if (pattern[i] == '\0') {

			if (ip != NULL)
				*ip = index;
			return (0);
		}
		if (pattern[i + 1] == '-' && pattern[i + 2] != '\0')
			i += 3;
		else
			i++;
	}
	if (ip != NULL)
		*ip = i;
	return (1);
}
