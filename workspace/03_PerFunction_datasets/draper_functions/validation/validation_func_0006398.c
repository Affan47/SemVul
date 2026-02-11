cry(struct mg_connection *conn, const char *fmt, ...) {
  char buf[MG_BUF_LEN], src_addr[20];
  va_list ap;
  FILE *fp;
  time_t timestamp;

  va_start(ap, fmt);
  (void) vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);


  conn->log_message = buf;
  if (call_user(conn, MG_EVENT_LOG) == NULL) {
    fp = conn->ctx == NULL || conn->ctx->config[ERROR_LOG_FILE] == NULL ? NULL :
      mg_fopen(conn->ctx->config[ERROR_LOG_FILE], "a+");

    if (fp != NULL) {
      flockfile(fp);
      timestamp = time(NULL);

      sockaddr_to_string(src_addr, sizeof(src_addr), &conn->client.rsa);
      fprintf(fp, "[%010lu] [error] [client %s] ", (unsigned long) timestamp,
              src_addr);

      if (conn->request_info.request_method != NULL) {
        fprintf(fp, "%s %s: ", conn->request_info.request_method,
                conn->request_info.uri);
      }

      (void) fprintf(fp, "%s", buf);
      fputc('\n', fp);
      funlockfile(fp);
      if (fp != stderr) {
        fclose(fp);
      }
    }
  }
  conn->log_message = NULL;
}
