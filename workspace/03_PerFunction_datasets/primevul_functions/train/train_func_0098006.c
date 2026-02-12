static SOCKET mg_open_listener(const char *url, struct mg_addr *addr) {
  SOCKET fd = INVALID_SOCKET;
  int s_err = 0;
  memset(addr, 0, sizeof(*addr));
  addr->port = mg_htons(mg_url_port(url));
  if (!mg_aton(mg_url_host(url), addr)) {
    LOG(LL_ERROR, ("invalid listening URL: %s", url));
  } else {
    union usa usa;
    socklen_t slen = tousa(addr, &usa);
    int on = 1, af = addr->is_ip6 ? AF_INET6 : AF_INET;
    int type = strncmp(url, "udp:", 4) == 0 ? SOCK_DGRAM : SOCK_STREAM;
    int proto = type == SOCK_DGRAM ? IPPROTO_UDP : IPPROTO_TCP;
    (void) on;

    if ((fd = socket(af, type, proto)) != INVALID_SOCKET &&
#if (!defined(_WIN32) || !defined(SO_EXCLUSIVEADDRUSE)) && \
    (!defined(LWIP_SOCKET) || (defined(LWIP_SOCKET) && SO_REUSE == 1))


        !setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, (char *) &on, sizeof(on)) &&
#endif
#if defined(_WIN32) && defined(SO_EXCLUSIVEADDRUSE) && !defined(WINCE)


        !setsockopt(fd, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char *) &on,
                    sizeof(on)) &&
#endif
        bind(fd, &usa.sa, slen) == 0 &&

        (type == SOCK_DGRAM || listen(fd, MG_SOCK_LISTEN_BACKLOG_SIZE) == 0)) {

      if (getsockname(fd, &usa.sa, &slen) == 0) {
        addr->port = usa.sin.sin_port;
#if MG_ENABLE_IPV6
        if (addr->is_ip6) addr->port = usa.sin6.sin6_port;
#endif
      }
      mg_set_non_blocking_mode(fd);
    } else if (fd != INVALID_SOCKET) {
      s_err = MG_SOCK_ERRNO;
      closesocket(fd);
      fd = INVALID_SOCKET;
    }
  }
  if (fd == INVALID_SOCKET) {
    if (s_err == 0) s_err = MG_SOCK_ERRNO;
    LOG(LL_ERROR, ("Failed to listen on %s, errno %d", url, s_err));
  }

  return fd;
}
