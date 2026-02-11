gnac_profiles_mgr_get_profiles_dir(void)
{
  saved_profiles_dir = g_build_filename(g_get_user_data_dir(),
      PACKAGE, "profiles", NULL);
  GFile *dir = g_file_new_for_path(saved_profiles_dir);
  if (g_file_query_exists(dir, NULL)) {
    return dir;
  }

  GError *error = NULL;

  if (!g_file_make_directory_with_parents(dir, NULL, &error)) {
    libgnac_warning("%s: %s",
        _("Unable to create the profiles directory"), error->message);
    g_clear_error(&error);
    return NULL;
  }

  return dir;
}
