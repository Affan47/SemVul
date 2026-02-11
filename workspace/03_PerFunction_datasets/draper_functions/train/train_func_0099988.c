photos_utils_get_pixbuf_format (GFile *file)
{
  GdkPixbufFormat *format;
  gchar *basename;
  gchar *path;
  gchar *suffix;

  g_return_val_if_fail (file != NULL, NULL);

  path = g_file_get_path (file);
  basename = g_path_get_basename (path);
  suffix = photos_utils_get_pixbuf_suffix_from_basename (basename);

  format = photos_utils_get_pixbuf_format_by_suffix (suffix);

  g_free (path);
  g_free (basename);
  g_free (suffix);

  return format;
}
