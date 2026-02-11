print_diff_string(const char *str, unsigned int indent_level)
{
	const char *c = str;
	unsigned int i;
	static const char *indent = "   ";

	for (i = 0; i < indent_level; i++)
		printf("%s", indent);
	for (; *c; c++) {
		if (*c == '\n') {
			if (*(c + 1) == '\0')
				break;
			printf("%c", *c);
			for (i = 0; i < indent_level; i++)
				printf("%s", indent);
		} else if (*c == '\t') {
			printf("%s", indent);
		} else {
			printf("%c", *c);
		}
	}
}
