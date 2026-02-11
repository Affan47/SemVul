remove_files (const gchar *dir,
              const gchar *fileprefix)
{
	GDir *d;

	g_return_if_fail (dir != NULL);
	g_return_if_fail (fileprefix != NULL);
	g_return_if_fail (*fileprefix != '\0');

	d = g_dir_open (dir, 0, NULL);
	if (d) {
		const gchar *entry;
		gint len = strlen (fileprefix);

		while ((entry = g_dir_read_name (d)) != NULL) {
			if (entry && strncmp (entry, fileprefix, len) == 0) {
				gchar *path;

				path = g_build_filename (dir, entry, NULL);
				if (!g_file_test (path, G_FILE_TEST_IS_DIR))
					g_unlink (path);
				g_free (path);
			}
		}
		g_dir_close (d);
	}
}
