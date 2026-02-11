print_with_linenumbers(FILE *output, char *lines,
					   const char *header_keyword)
{
	bool		in_header = (header_keyword != NULL);
	size_t		header_sz = in_header ? strlen(header_keyword) : 0;
	int			lineno = 0;

	while (*lines != '\0')
	{
		char	   *eol;

		if (in_header && strncmp(lines, header_keyword, header_sz) == 0)
			in_header = false;


		if (!in_header)
			lineno++;


		eol = strchr(lines, '\n');
		if (eol != NULL)
			*eol = '\0';


		if (in_header)
			fprintf(output, "        %s\n", lines);
		else
			fprintf(output, "%-7d %s\n", lineno, lines);


		if (eol == NULL)
			break;
		lines = ++eol;
	}
}
