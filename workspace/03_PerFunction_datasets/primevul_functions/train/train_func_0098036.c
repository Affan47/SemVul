void mg_resolve(struct mg_connection *c, const char *url) {
  struct mg_str host = mg_url_host(url);
  c->peer.port = mg_htons(mg_url_port(url));
  if (mg_aton(host, &c->peer)) {

    mg_connect_resolved(c);
  } else {

    mg_sendnsreq(c, &host, c->mgr->dnstimeout, &c->mgr->dns4, false);
  }
}
