wait_until_socket_is_readable(struct mg_connection *conn) {
  int result;
  struct timeval tv;
  fd_set set;

  do {
    tv.tv_sec = 0;
    tv.tv_usec = 300 * 1000;
    FD_ZERO(&set);
    FD_SET(conn->client.sock, &set);
    result = select(conn->client.sock + 1, &set, NULL, NULL, &tv);
    if(result == 0 && conn->ssl != NULL) {
        result = SSL_pending(conn->ssl);
    }
  } while ((result == 0 || (result < 0 && ERRNO == EINTR)) &&
           conn->ctx->stop_flag == 0);

  return conn->ctx->stop_flag || result < 0 ? 0 : 1;
}
