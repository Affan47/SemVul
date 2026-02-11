HTTPServer_new(const char * ip_address, uint16_t port, HTTPServerHandler handler) {
  struct HTTPServer * result = xmalloc(sizeof(struct HTTPServer));
  if (ip_address == NULL) {
    result->ip_address = NULL;
  }
  else {
    result->ip_address = xstrdup(ip_address);
  }
  result->port = port;
  result->handler = handler;
  result->s = -1;
  return result;
}
