gsb_file_util_get_contents ( gchar *filename,
				      gchar **file_content,
				      gulong *length )
{
    gzFile file;
    struct stat stat_buf;
    gulong alloc_size;
    gulong orig_size;
    gchar *content;
    gulong iterator = 0;
    gulong bytes_read;
    gboolean eof = 0;
	gchar *os_filename;

#ifdef _MSC_VER
	os_filename = g_locale_from_utf8(filename, -1, NULL, NULL, NULL);
#else
	os_filename = g_strdup(filename);
#endif

    file = gzopen (os_filename, "rb");
    if (!file)
	return FALSE;


    if (stat (os_filename, &stat_buf))
    {
	gchar *tmpstr = g_strdup_printf ( _("Grisbi cannot stat file %s, please check the file."),
					  os_filename);
	dialogue_error (tmpstr);
	g_free (tmpstr);
	return FALSE;
    }

    orig_size = stat_buf.st_size;
#ifndef _WIN32
    if (gzdirect (file))

	alloc_size = orig_size + 1;
    else
#endif


	alloc_size = 20 * orig_size;

    content = g_malloc0 (alloc_size);
    if (!content)
    {
	dialogue_error_memory ();
	return FALSE;
    }

    bytes_read = 0;


    iterator = gzread (file, content, orig_size);

    if (iterator < 0)
    {
	int save_errno = errno;
	gchar *tmpstr;

	g_free (content);
	tmpstr = g_strdup_printf ( _("Failed to read from file '%s': %s"),
				   os_filename, g_strerror (save_errno));
	dialogue_error (tmpstr);
	g_free (tmpstr);
	return FALSE;
    }


    do
    {
	gchar c;

	c = gzgetc (file);

	eof = gzeof (file);
	if (!eof)
	{
	    content[iterator] = c;
	    iterator++;

	    if (iterator >= alloc_size)
	    {


		devel_debug ("Realloc is needed, if this message comes often, please contact the Grisbi team to improve the software ;-)");
		alloc_size = alloc_size + orig_size;
		content = g_realloc (content, alloc_size);

		if (!content)
		{
		    dialogue_error_memory ();
		    return FALSE;
		}
	    }
	}
    }
    while (!eof);

    content[iterator] = '\0';


    *length = iterator;
    *file_content = content;

    gzclose (file);
	g_free(os_filename);
    return TRUE;
}
