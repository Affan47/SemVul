bool HHVM_FUNCTION(socket_shutdown,
                   const Resource& socket,
                   int how ) {


  if (socket->instanceof<MemFile>()) {
    return true;
  }
  auto sock = cast<Socket>(socket);
  if (shutdown(sock->fd(), how) != 0) {
    SOCKET_ERROR(sock, "unable to shutdown socket", errno);
    return false;
  }
  return true;
}
