static void test_packed(void) {
  struct mg_mgr mgr;
  const char *url = "http://127.0.0.1:12351";
  char buf[FETCH_BUF_SIZE] = "", *data = mg_file_read("Makefile", NULL);
  mg_mgr_init(&mgr);
  mg_http_listen(&mgr, url, eh7, NULL);


  ASSERT(fetch(&mgr, buf, url, "GET /Makefile HTTP/1.0\n\n") == 200);
  ASSERT(cmpbody(buf, data) == 0);
  free(data);


  data = mg_file_read("src/ssi.h", NULL);
  ASSERT(fetch(&mgr, buf, url, "GET /src/ssi.h HTTP/1.0\n\n") == 200);
  ASSERT(cmpbody(buf, data) == 0);
  free(data);


  ASSERT(fetch(&mgr, buf, url, "GET / HTTP/1.0\n\n") == 200);


  ASSERT(fetch(&mgr, buf, url, "GET /test HTTP/1.0\n\n") == 301);
  ASSERT(fetch(&mgr, buf, url, "GET /test/ HTTP/1.0\n\n") == 200);


  mg_mgr_free(&mgr);
  ASSERT(mgr.conns == NULL);
}
