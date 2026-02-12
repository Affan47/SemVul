file_peek_path_generic (GFile *file)
{
  const char *path;
  static GQuark _file_path_quark = 0;

  if (G_UNLIKELY (_file_path_quark) == 0)
    _file_path_quark = g_quark_from_static_string ("gio-file-path");


  while (TRUE)
    {
      gchar *new_path = NULL;

      path = g_object_get_qdata ((GObject*)file, _file_path_quark);

      if (path != NULL)
        break;

      if (g_file_has_uri_scheme (file, "trash") ||
          g_file_has_uri_scheme (file, "recent"))
        new_path = file_get_target_path (file);
      else
        new_path = g_file_get_path (file);
      if (new_path == NULL)
        return NULL;


      if (g_object_replace_qdata ((GObject *) file, _file_path_quark,
                                  NULL, (gpointer) new_path,
                                  (GDestroyNotify) g_free, NULL))
        break;
      else
        g_free (new_path);
    }

  return path;
}
