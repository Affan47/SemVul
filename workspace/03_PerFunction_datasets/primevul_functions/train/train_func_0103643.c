plugin_parse_directory (Ekiga::KickStart& kickstart,
			const gchar* path)
{
  g_return_if_fail (path != NULL);

  GError* error = NULL;
  GDir* directory = g_dir_open (path, 0, &error);

#if DEBUG
  std::cout << "Trying to load plugins in " << path << "... ";
#endif

  if (directory != NULL) {

#if DEBUG
    std::cout << "open succeeded" << std::endl;
#endif
    const gchar* name = g_dir_read_name (directory);

    while (name) {

      gchar* filename = g_build_filename (path, name, NULL);


      if (g_str_has_suffix (filename, G_MODULE_SUFFIX))
	plugin_parse_file (kickstart, filename);
      else
	plugin_parse_directory (kickstart, filename);

      g_free (filename);
      name = g_dir_read_name (directory);
    }

    g_dir_close (directory);
  } else {

#if DEBUG
    std::cout << "failure: " << error->message << std::endl;
#endif
    g_error_free (error);
  }
}
