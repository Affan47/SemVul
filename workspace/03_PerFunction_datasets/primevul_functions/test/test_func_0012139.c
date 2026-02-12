get_line(gerb_file_t *fd)
{
	int read;
	gchar *retstring;
	gchar *tmps=g_strdup("");

	read = gerb_fgetc(fd);
	while (read != '\n' && read != '\r' && read != EOF) {
		retstring = g_strdup_printf("%s%c", tmps, read);


		if (tmps)  {
			g_free (tmps);
			tmps = NULL;
		}
		tmps = retstring;
		read = gerb_fgetc(fd);
	}


	if (read != EOF)
	    gerb_ungetc(fd);

	return tmps;
}
