forward_put_data(struct connection *conn) {
  struct iobuf *io = &conn->ns_conn->recv_iobuf;
  size_t k = (size_t) ((conn->cl < (int64_t) io->len) ? conn->cl : io->len);
  int n = write(conn->endpoint.fd, io->buf, k);
  if (n > 0) {
    iobuf_remove(io, n);
    conn->cl -= n;
  }
  if (conn->cl <= 0) {
    close_local_endpoint(conn);
  }
}
