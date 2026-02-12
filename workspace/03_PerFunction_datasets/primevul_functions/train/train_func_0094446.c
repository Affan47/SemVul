SSLNetVConnection::do_io_close(int lerrno)
{
  if (this->ssl != nullptr && sslHandShakeComplete) {
    callHooks(TS_EVENT_VCONN_CLOSE);
    int shutdown_mode = SSL_get_shutdown(ssl);
    Debug("ssl-shutdown", "previous shutdown state 0x%x", shutdown_mode);
    int new_shutdown_mode = shutdown_mode | SSL_RECEIVED_SHUTDOWN;

    if (new_shutdown_mode != shutdown_mode) {


      Debug("ssl-shutdown", "new SSL_set_shutdown 0x%x", new_shutdown_mode);
      SSL_set_shutdown(ssl, new_shutdown_mode);
    }


    char c;
    ssize_t x = recv(this->con.fd, &c, 1, MSG_PEEK);

    bool do_shutdown = (x > 0);
    if (x < 0) {
      do_shutdown = (errno == EAGAIN || errno == EWOULDBLOCK);
    }
    if (do_shutdown) {

      int ret = SSL_shutdown(ssl);
      Debug("ssl-shutdown", "SSL_shutdown %s", (ret) ? "success" : "failed");
    } else {

      SSL_set_quiet_shutdown(ssl, 1);
      SSL_set_shutdown(ssl, SSL_RECEIVED_SHUTDOWN | SSL_SENT_SHUTDOWN);
      Debug("ssl-shutdown", "Enable quiet shutdown");
    }
  }

  super::do_io_close(lerrno);
}
