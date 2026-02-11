query_log_open (const char *kb_name)
{
  char *filename = g_strdup_printf("/var/log/4store/query-%s.log", kb_name);

  ql_file= fopen(filename, "a");
  if (ql_file) {
    fprintf(ql_file, "\n# 4s-httpd for KB=%s, pid=%d #####\n", kb_name, getpid());
    fflush(ql_file);
  } else {
    fs_error(LOG_WARNING, "couldn't open query log '%s' for appending: %s", filename, strerror(errno));
  }
  g_free(filename);
}
