host_ntoa(int type, const void *arg, uschar *buffer, int *portptr)
{
uschar *yield;


#if HAVE_IPV6
uschar addr_buffer[46];
if (type < 0)
  {
  int family = ((struct sockaddr *)arg)->sa_family;
  if (family == AF_INET6)
    {
    struct sockaddr_in6 *sk = (struct sockaddr_in6 *)arg;
    yield = US inet_ntop(family, &(sk->sin6_addr), CS addr_buffer,
      sizeof(addr_buffer));
    if (portptr != NULL) *portptr = ntohs(sk->sin6_port);
    }
  else
    {
    struct sockaddr_in *sk = (struct sockaddr_in *)arg;
    yield = US inet_ntop(family, &(sk->sin_addr), CS addr_buffer,
      sizeof(addr_buffer));
    if (portptr != NULL) *portptr = ntohs(sk->sin_port);
    }
  }
else
  {
  yield = US inet_ntop(type, arg, CS addr_buffer, sizeof(addr_buffer));
  }


if (Ustrncmp(yield, "::ffff:", 7) == 0) yield += 7;

#else


if (type < 0)
  {
  yield = US inet_ntoa(((struct sockaddr_in *)arg)->sin_addr);
  if (portptr != NULL) *portptr = ntohs(((struct sockaddr_in *)arg)->sin_port);
  }
else
  yield = US inet_ntoa(*((struct in_addr *)arg));
#endif


if (buffer == NULL) return string_copy(yield);


Ustrcpy(buffer, yield);
return buffer;
}
