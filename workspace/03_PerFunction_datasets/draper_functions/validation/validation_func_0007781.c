cleanup(CleanupStage)
{
  if (_socket_fd >= 0) {

#ifdef SHUT_RDWR
    shutdown(_socket_fd, SHUT_RDWR);
#else
    shutdown(_socket_fd, 2);
#endif
    close(_socket_fd);
    if (!_tcp_socket)
      unlink(_unix_pathname.c_str());
    _socket_fd = -1;
  }

  for (int i = 0; i < _fd_alive.size(); i++)
    if (_fd_alive[i]) {
      close(i);
      _fd_alive[i] = 0;
    }
  _live_fds = 0;

  if (_retry_timer) {
    delete _retry_timer;
    _retry_timer = 0;
  }


  if (_channel == "default")
    remove_chatter_channel(chatter_socket_errh, this);
  else
    remove_chatter_channel
      ((ChatterSocketErrorHandler *&)(router()->force_attachment("ChatterChannel." + _channel)), this);
}
