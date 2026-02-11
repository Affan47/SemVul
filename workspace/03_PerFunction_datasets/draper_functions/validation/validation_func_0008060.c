homebank_lastopenedfiles_load(void)
{
GKeyFile *keyfile;
gboolean retval = FALSE;
gchar *group, *filename, *lastfilename;

	DB( g_print("\n[homebank] lastopenedfiles load\n") );

	keyfile = g_key_file_new();
	if(keyfile)
	{

		filename = g_build_filename(homebank_app_get_config_dir(), "lastopenedfiles", NULL );

		DB( g_print(" -> filename: %s\n", filename) );

		if(g_key_file_load_from_file (keyfile, filename, G_KEY_FILE_NONE, NULL))
		{
			group = "HomeBank";

            DB( g_print(" -> load keyfile ok\n") );

			if(g_key_file_has_key(keyfile, group, "LastOpenedFile", NULL))
			{
                DB( g_print(" -> keyfile has key ok\n") );

				lastfilename = g_key_file_get_string  (keyfile, group, "LastOpenedFile", NULL);

				DB( g_print(" -> lastfile loaded: %s\n", lastfilename ) );

				if (g_file_test (lastfilename, G_FILE_TEST_EXISTS) != FALSE)
				{
					DB( g_print(" -> file exists\n") );

					hbfile_change_filepath(lastfilename);

					retval = TRUE;
				}
			}
		}
		g_free(filename);
		g_key_file_free (keyfile);
	}

	DB( g_print(" -> return: %d\n", retval) );

	return retval;
}
