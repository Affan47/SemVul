buffer_read_line(struct line_buffer *buf)
{
	char *end;
	if (!fgets(buf->line_buffer, sizeof(buf->line_buffer), buf->infile))

		return NULL;
	end = buf->line_buffer + strlen(buf->line_buffer);
	if (end[-1] == '\n')
		end[-1] = '\0';
	else if (feof(buf->infile))
		;
	else


		return NULL;
	return buf->line_buffer;
}
