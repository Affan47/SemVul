static bool send_fd(int afdt_fd, int fd) {
  afdt_error_t err;
  errno = 0;
  int ret = afdt_send_fd_msg(afdt_fd, 0, 0, fd, &err);
  if (ret < 0 && errno == 0) {

    errno = EPROTO;
  }
  return ret >= 0;
}
