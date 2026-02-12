static bool set_sockaddr(sockaddr_storage &sa_storage, req::ptr<Socket> sock,
                         const String& addr, int port,
                         struct sockaddr *&sa_ptr, size_t &sa_size) {


  memset(&sa_storage, 0, sizeof(struct sockaddr_storage));
  struct sockaddr *sock_type = (struct sockaddr*) &sa_storage;
  switch (sock->getType()) {
  case AF_UNIX:
    {
#ifdef _MSC_VER
      return false;
#else
      struct sockaddr_un *sa = (struct sockaddr_un *)sock_type;
      sa->sun_family = AF_UNIX;
      if (addr.length() > sizeof(sa->sun_path)) {
        raise_warning(
          "Unix socket path length (%ld) is larger than system limit (%lu)",
          addr.length(),
          sizeof(sa->sun_path)
        );
        return false;
      }
      memcpy(sa->sun_path, addr.data(), addr.length());
      sa_ptr = (struct sockaddr *)sa;
      sa_size = offsetof(struct sockaddr_un, sun_path) + addr.length();
#ifdef __linux__
      if (addr.length() == 0) {


        sa_size = offsetof(struct sockaddr_un, sun_path);
      }
#endif

#endif
    }
    break;
  case AF_INET:
    {
      struct sockaddr_in *sa = (struct sockaddr_in *)sock_type;
      sa->sin_family = AF_INET;
      sa->sin_port = htons((unsigned short) port);
      if (!php_set_inet_addr(sa, addr.c_str(), sock)) {
        return false;
      }
      sa_ptr = (struct sockaddr *)sa;
      sa_size = sizeof(struct sockaddr_in);
    }
    break;
  case AF_INET6:
    {
      struct sockaddr_in6 *sa = (struct sockaddr_in6 *)sock_type;
      sa->sin6_family = AF_INET6;
      sa->sin6_port = htons((unsigned short) port);
      if (!php_set_inet6_addr(sa, addr.c_str(), sock)) {
        return false;
      }
      sa_ptr = (struct sockaddr *)sa;
      sa_size = sizeof(struct sockaddr_in6);
    }
    break;
  default:
    raise_warning("unsupported socket type '%d', must be "
                    "AF_UNIX, AF_INET, or AF_INET6", sock->getType());
    return false;
  }
#ifdef __APPLE__


  sa_ptr->sa_len = sa_size;
#endif
  return true;
}
