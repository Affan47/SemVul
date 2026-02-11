add_listener(int port, const char* vhost_ip, const char* mask,
                  const struct ListenerFlags *flags)
{
  struct Listener* listener;
  struct irc_in_addr vaddr;
  int okay = 0;
  int new_listener = 0;
  int fd;


  if (0 == port)
    return;

  memset(&vaddr, 0, sizeof(vaddr));

  if (!EmptyString(vhost_ip)
      && strcmp(vhost_ip, "*")
      && !ircd_aton(&vaddr, vhost_ip))
      return;

  listener = find_listener(port, &vaddr);
  if (!listener)
  {
    new_listener = 1;
    listener = make_listener(port, &vaddr);
  }
  memcpy(&listener->flags, flags, sizeof(listener->flags));
  FlagSet(&listener->flags, LISTEN_ACTIVE);
  if (mask)
    ipmask_parse(mask, &listener->mask, &listener->mask_bits);
  else
    listener->mask_bits = 0;

#ifdef IPV6
  if (FlagHas(&listener->flags, LISTEN_IPV6)) {
    if (listener->fd_v6 >= 0) {
      set_listener_options(listener, listener->fd_v6);
      okay = 1;
    } else if ((fd = inetport(listener, AF_INET6)) >= 0) {
      listener->fd_v6 = fd;
      okay = 1;
    }
  } else if (-1 < listener->fd_v6) {
    close(listener->fd_v6);
    socket_del(&listener->socket_v6);
    listener->fd_v6 = -1;
  }
#endif

  if (FlagHas(&listener->flags, LISTEN_IPV4)) {
    if (listener->fd_v4 >= 0) {
      set_listener_options(listener, listener->fd_v4);
      okay = 1;
    } else if ((fd = inetport(listener, AF_INET)) >= 0) {
      listener->fd_v4 = fd;
      okay = 1;
    }
  } else if (-1 < listener->fd_v4) {
    close(listener->fd_v4);
    socket_del(&listener->socket_v4);
    listener->fd_v4 = -1;
  }

  if (!okay)
    free_listener(listener);
  else if (new_listener) {
    listener->next   = ListenerPollList;
    ListenerPollList = listener;
  }
}
