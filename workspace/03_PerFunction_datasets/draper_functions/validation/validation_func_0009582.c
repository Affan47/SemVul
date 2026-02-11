http_line(client_ctxt *ctxt, gchar *line)
{
  if (!ctxt->request) {

    ctxt->request = g_strchomp(line);
  } else if (!strcmp(line, "\r\n")) {
    http_request(ctxt, ctxt->request);
    free(line);
  } else {

    char *name = line;
    char *colon = strchr(line, ':');
    char *value;
    if (colon) {
      value = colon + 1;
      g_hash_table_insert(ctxt->headers, g_ascii_strdown(name, colon - name), g_strdup(g_strstrip(value)));
    }
    free(line);
  }
}
