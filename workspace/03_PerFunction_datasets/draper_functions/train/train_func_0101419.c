build_create_shellscript(const gchar *fname, const gchar *cmd, gboolean autoclose, GError **error)
{
	FILE *fp;
	gchar *str;
	gboolean success = TRUE;
#ifdef G_OS_WIN32
	gchar *expanded_cmd;
#endif

	fp = g_fopen(fname, "w");
	if (! fp)
	{
		set_file_error_from_errno(error, errno, "Failed to create file");
		return FALSE;
	}
#ifdef G_OS_WIN32

	expanded_cmd = win32_expand_environment_variables(cmd);
	str = g_strdup_printf("%s\n\n%s\ndel \"%%0\"\n\npause\n", expanded_cmd, (autoclose) ? "" : "pause");
	g_free(expanded_cmd);
#else
	str = g_strdup_printf(
		"#!/bin/sh\n\nrm $0\n\n%s\n\necho \"\n\n------------------\n(program exited with code: $?)\" \
		\n\n%s\n", cmd, (autoclose) ? "" :
		"\necho \"Press return to continue\"\n#to be more compatible with shells like "
			"dash\ndummy_var=\"\"\nread dummy_var");
#endif

	if (fputs(str, fp) < 0)
	{
		set_file_error_from_errno(error, errno, "Failed to write file");
		success = FALSE;
	}
	g_free(str);

	if (fclose(fp) != 0)
	{
		if (error && ! *error)
			set_file_error_from_errno(error, errno, "Failed to close file");
		success = FALSE;
	}

	return success;
}
