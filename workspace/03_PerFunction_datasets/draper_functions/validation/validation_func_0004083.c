addrmask_to_string(struct string *target, struct addr_info *addr)
{
  char buffer[NI_MAXHOST];
#ifdef WIN32
  int res;
  struct sockaddr_storage sock;
  socklen_t len;
#endif

  if (!target || !addr)
    return false;

#ifndef WIN32
  if (inet_ntop(addr->addr_family, addr->net_bytes, buffer, sizeof(buffer)) == NULL) {
    return false;
  }
#else
  memset(&sock, 0, sizeof(sock));
  if (addr->addr_family == AF_INET) {
    struct sockaddr_in *sock4 = (struct sockaddr_in *) &sock;
    len = sizeof(struct sockaddr_in);

    sock4->sin_family = addr->addr_family;
    memcpy(&sock4->sin_addr.s_addr, addr->net_bytes, addr->addr_byte_count);
  } else if (addr->addr_family == AF_INET6) {
    struct sockaddr_in6 *sock6 = (struct sockaddr_in6 *) &sock;
    len = sizeof(struct sockaddr_in6);

    sock6->sin6_family = addr->addr_family;
    memcpy(sock6->sin6_addr.s6_addr, addr->net_bytes, addr->addr_byte_count);
  } else {
    return false;
  }

  res = getnameinfo((struct sockaddr *) &sock, len, buffer, sizeof(buffer), NULL, 0, NI_NUMERICHOST);
  if (res != 0) {
    log_err("addrmask_to_string: getnameinfo() failed: %s", gai_strerror(res));
    return false;
  }
#endif

  if (!string_concat(target, buffer))
    return false;
  if (!string_putc(target, '/'))
    return false;

  if (!string_putint(target, addr->mask_shift))
    return false;

  return true;
}
