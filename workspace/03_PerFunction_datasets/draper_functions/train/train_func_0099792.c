ns_parse_port_string(const char *str, union socket_address *sa) {
  unsigned int a, b, c, d, port;
  int len = 0;
#ifdef NS_ENABLE_IPV6
  char buf[100];
#endif


  memset(sa, 0, sizeof(*sa));
  sa->sin.sin_family = AF_INET;

  if (sscanf(str, "%u.%u.%u.%u:%u%n", &a, &b, &c, &d, &port, &len) == 5) {

    sa->sin.sin_addr.s_addr = htonl((a << 24) | (b << 16) | (c << 8) | d);
    sa->sin.sin_port = htons((uint16_t) port);
#ifdef NS_ENABLE_IPV6
  } else if (sscanf(str, "[%49[^]]]:%u%n", buf, &port, &len) == 2 &&
             inet_pton(AF_INET6, buf, &sa->sin6.sin6_addr)) {

    sa->sin6.sin6_family = AF_INET6;
    sa->sin6.sin6_port = htons((uint16_t) port);
#endif
  } else if (sscanf(str, "%u%n", &port, &len) == 1) {

    sa->sin.sin_port = htons((uint16_t) port);
  } else {
    port = 0;
  }

  return port <= 0xffff && str[len] == '\0';
}
