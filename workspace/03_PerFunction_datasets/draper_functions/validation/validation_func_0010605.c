uv__udp_bind(uv_udp_t* handle,
                        int domain,
                        struct sockaddr* addr,
                        socklen_t len,
                        unsigned flags) {
  int saved_errno;
  int status;
  int yes;
  int fd;

  saved_errno = errno;
  status = -1;


  if (flags & ~UV_UDP_IPV6ONLY) {
    uv_err_new(handle->loop, EINVAL);
    goto out;
  }


  if ((flags & UV_UDP_IPV6ONLY) && domain != AF_INET6) {
    uv_err_new(handle->loop, EINVAL);
    goto out;
  }


  if (handle->fd != -1) {
    uv_err_new_artificial(handle->loop, UV_EALREADY);
    goto out;
  }

  if ((fd = uv__socket(domain, SOCK_DGRAM, 0)) == -1) {
    uv_err_new(handle->loop, errno);
    goto out;
  }

  if (flags & UV_UDP_IPV6ONLY) {
#ifdef IPV6_V6ONLY
    yes = 1;
    if (setsockopt(fd, IPPROTO_IPV6, IPV6_V6ONLY, &yes, sizeof yes) == -1) {
      uv_err_new(handle->loop, errno);
      goto out;
    }
#else
    uv_err_new((uv_handle_t*)handle, ENOTSUP);
    goto out;
#endif
  }

  if (bind(fd, addr, len) == -1) {
    uv_err_new(handle->loop, errno);
    goto out;
  }

  handle->fd = fd;
  status = 0;

out:
  if (status)
    uv__close(fd);

  errno = saved_errno;
  return status;
}
