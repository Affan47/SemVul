s_toplevel_read_page(TOPLEVEL *toplevel, char *filename)
{
  int file_return_code;
  GError *err = NULL;


  toplevel->page_current->page_filename = g_strdup(filename);


  file_return_code = f_open (toplevel, toplevel->page_current, filename, &err);


  if (err != NULL) {
    g_warning ("%s", err->message);
    g_error_free (err);
  }

  return file_return_code;
}
