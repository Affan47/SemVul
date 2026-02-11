migrate_rename (const gchar *old_filename,
                const gchar *new_filename)
{
	gboolean old_filename_is_dir;
	gboolean old_filename_exists;
	gboolean new_filename_exists;
	gboolean success = TRUE;

	old_filename_is_dir = g_file_test (old_filename, G_FILE_TEST_IS_DIR);
	old_filename_exists = g_file_test (old_filename, G_FILE_TEST_EXISTS);
	new_filename_exists = g_file_test (new_filename, G_FILE_TEST_EXISTS);

	if (!old_filename_exists)
		return TRUE;

	g_print ("  mv %s %s\n", old_filename, new_filename);


	if (old_filename_is_dir || !new_filename_exists) {
		if (g_rename (old_filename, new_filename) < 0) {
			g_printerr ("  FAILED: %s\n", g_strerror (errno));
			success = FALSE;
		}
	} else {
		g_printerr ("  FAILED: Destination file already exists\n");
		success = FALSE;
	}

	return success;
}
