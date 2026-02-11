glurp_filename(gchar *path) {
  gchar **dirs = g_strsplit(path, "/", 0);
  gint i = 0;

  while( dirs[i+1] ) i++;
  return dirs[i];
}
