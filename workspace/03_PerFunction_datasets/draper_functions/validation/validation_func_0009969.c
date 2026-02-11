show_response(struct http_request* req, struct http_response* res) {

  dump_http_request(req);

  if (FETCH_FAIL(res)) {
    SAY("^^^ REQUEST SHOWN ABOVE CAUSED ERROR: %d ^^^\n", res->state);
    return 0;
  }

  dump_http_response(res);

  return 0;

}
