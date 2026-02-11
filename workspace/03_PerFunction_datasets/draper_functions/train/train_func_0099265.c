read_line(const char *prompt)
{
	int sz;

	sz = read_line_input(prompt, line_buffer, sizeof(line_buffer), NULL);
	if (sz <= 0)
		exit(EXIT_SUCCESS);

	if (line_buffer[sz-1] == '\n')
		line_buffer[--sz] = '\0';

	line_ptr = line_buffer;
	while (*line_ptr != '\0' && (unsigned char)*line_ptr <= ' ')
		line_ptr++;
	return *line_ptr;
}
