g3d_read_cstr(FILE *f, gchar *buffer, gint32 max_len)
{
	gint32 n = 0;
	gchar c;

	do
	{
		c = g3d_read_int8(f);
		buffer[n] = c;
		n ++;
	}
	while((c != 0) && (n < max_len));

	buffer[max_len - 1] = '\0';

	return n;
}
