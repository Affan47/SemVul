exo_open_find_scheme (const gchar *string)
{
  gchar *current_dir;
  gchar *uri;
  gchar *path;


  if (g_path_is_absolute (string))
    return exo_open_get_path (string);


  current_dir = g_get_current_dir ();
  path = g_build_filename (current_dir, string, NULL);
  g_free (current_dir);


  if (g_file_test (path, G_FILE_TEST_EXISTS))
    {
       uri = exo_open_get_path (path);
       g_free (path);
       return uri;
    }
  g_free (path);


  if (g_regex_match_simple (MATCH_PATTERN_EMAIL, string, G_REGEX_CASELESS, 0))
    return g_strconcat ("mailto:", string, NULL);


  if (g_regex_match_simple (MATCH_PATTERN_HTTP, string, G_REGEX_CASELESS, 0))
    return g_strconcat ("http://", string, NULL);

  return NULL;
}
