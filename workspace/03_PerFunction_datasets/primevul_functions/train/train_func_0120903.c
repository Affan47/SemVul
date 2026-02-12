static int find_boundary(multipart_buffer *self, char *boundary TSRMLS_DC)
{
	char *line;


	while( (line = get_line(self TSRMLS_CC)) )
	{

		if (!strcmp(line, boundary)) {
			return 1;
		}
	}


	return 0;
}
