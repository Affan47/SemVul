bindresvport (int sd, struct sockaddr_in *sin)
{
  static short startport = STARTPORT;
  static short port;
  struct sockaddr_in myaddr;
  int i;

  if (!blacklist_read)
    load_blacklist ();

  if (sin == (struct sockaddr_in *) 0)
    {
      sin = &myaddr;
      __bzero (sin, sizeof (*sin));
      sin->sin_family = AF_INET;
    }
  else if (sin->sin_family != AF_INET)
    {
      __set_errno (EAFNOSUPPORT);
      return -1;
    }

  if (port == 0)
    {
      port = (__getpid () % NPORTS) + STARTPORT;
    }

  __set_errno (EADDRINUSE);

  int res = -1;

  int nports = ENDPORT - startport + 1;
  int endport = ENDPORT;

  __libc_lock_lock (lock);

 again:
  for (i = 0; i < nports; ++i)
    {
      int j;

      sin->sin_port = htons (port);


      for (j = 0; j < list_size; j++)
	if (port == list[j])
	  goto try_next_port;

      res = __bind (sd, sin, sizeof (struct sockaddr_in));
      if (res >= 0 || errno != EADDRINUSE)
	break;

try_next_port:
      if (++port > endport)
	port = startport;
    }

  if (i == nports && startport != LOWPORT)
    {
      startport = LOWPORT;
      endport = STARTPORT - 1;
      nports = STARTPORT - LOWPORT;
      port = LOWPORT + port % (STARTPORT - LOWPORT);
      goto again;
    }

  __libc_lock_unlock (lock);

  return res;
}
