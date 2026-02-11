reader_get_next_filepath (JournalReader *jreader)
{
	gchar *filename_open = NULL;
	gchar *test;

	test = g_strdup_printf ("%s.%d", jreader->filename, jreader->current_file + 1);

	if (g_file_test (test, G_FILE_TEST_EXISTS)) {
		jreader->current_file++;
		filename_open = test;
	} else {
		gchar *filename;
		GFile *dest_dir, *possible;


		if (rotating_settings.rotate_to) {
			dest_dir = g_file_new_for_path (rotating_settings.rotate_to);
		} else {
			GFile *source;


			source = g_file_new_for_path (test);
			dest_dir = g_file_get_parent (source);
			g_object_unref (source);
		}

		filename = g_path_get_basename (test);
		g_free (test);
		test = filename;
		filename = g_strconcat (test, ".gz", NULL);
		g_free (test);
		possible = g_file_get_child (dest_dir, filename);
		g_object_unref (dest_dir);
		g_free (filename);

		if (g_file_query_exists (possible, NULL)) {
			jreader->current_file++;
			filename_open = g_file_get_path (possible);
		}
		g_object_unref (possible);
	}

	if (filename_open == NULL) {
		filename_open = g_strdup (jreader->filename);

		jreader->current_file = 0;
	}

	return filename_open;
}
