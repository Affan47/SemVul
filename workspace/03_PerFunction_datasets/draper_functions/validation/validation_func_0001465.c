proxy_request(struct ns_connection *pc, struct mg_connection *c) {
  int i, sent_close_header = 0;

  ns_printf(pc, "%s %s%s%s HTTP/%s\r\n", c->request_method, c->uri,
            c->query_string ? "?" : "",
            c->query_string ? c->query_string : "",
            c->http_version);
  for (i = 0; i < c->num_headers; i++) {
    if (mg_strcasecmp(c->http_headers[i].name, "Connection") == 0) {


      ns_printf(pc, "%s: %s\r\n", "Connection", "close");
      sent_close_header = 1;
    } else {
      ns_printf(pc, "%s: %s\r\n", c->http_headers[i].name,
                c->http_headers[i].value);
    }
  }
  if (!sent_close_header) {
    ns_printf(pc, "%s: %s\r\n", "Connection", "close");
  }
  ns_printf(pc, "%s", "\r\n");
  ns_send(pc, c->content, c->content_len);

}
