ssh_socket_get_poll_flags(ssh_socket s) {
  int r = 0;
  if (s->poll_in != NULL && (ssh_poll_get_events (s->poll_in) & POLLIN) > 0) {
    r |= SSH_READ_PENDING;
  }
  if (s->poll_out != NULL && (ssh_poll_get_events (s->poll_out) & POLLOUT) > 0) {
    r |= SSH_WRITE_PENDING;
  }
  return r;
}
