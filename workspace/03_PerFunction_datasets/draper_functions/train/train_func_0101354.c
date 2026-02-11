read_ssl(int sock, SSL *ssl, char *buff) {
  if(ssl) {
    return SSL_read(ssl, buff, 65535);
  } else {
    return recv(sock, buff, 65535, 0);
  }
}
