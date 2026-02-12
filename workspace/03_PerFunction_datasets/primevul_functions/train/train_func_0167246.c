empathy_adium_path_is_valid (const gchar *path)
{
	gboolean ret;
	gchar   *file;


	file = g_build_filename (path, "Contents", "Info.plist",
				 NULL);
	ret = g_file_test (file, G_FILE_TEST_EXISTS);
	g_free (file);

	if (!ret)
		return FALSE;


	file = g_build_filename (path, "Contents", "Resources", "Content.html",
				 NULL);
	ret = g_file_test (file, G_FILE_TEST_EXISTS);
	g_free (file);

	if (!ret) {
		file = g_build_filename (path, "Contents", "Resources", "Incoming",
					 "Content.html", NULL);
		ret = g_file_test (file, G_FILE_TEST_EXISTS);
		g_free (file);
	}

	return ret;
}
