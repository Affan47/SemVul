conn_open(EpmdVars *g,int fd)
{
  int i;
  Connection *s;

#ifdef VXWORKS


  if (fd >= FD_SETSIZE) {
      dbg_tty_printf(g,0,"file descriptor %d: too high for FD_SETSIZE=%d",
		     fd,FD_SETSIZE);
      close(fd);
      return EPMD_FALSE;
  }
#endif

  for (i = 0; i < g->max_conn; i++) {
    if (g->conn[i].open == EPMD_FALSE) {
      struct sockaddr_in si;
      struct sockaddr_in di;
#ifdef HAVE_SOCKLEN_T
      socklen_t st;
#else
      int st;
#endif
      st = sizeof(si);

      g->active_conn++;
      s = &g->conn[i];


      select_fd_set(g, fd);

      s->fd   = fd;
      s->open = EPMD_TRUE;
      s->keep = EPMD_FALSE;


      if (getpeername(s->fd,(struct sockaddr*) &si,&st) ||
	  st < sizeof(si)) {

	  s->local_peer = EPMD_FALSE;
      } else {


	  s->local_peer =
	      (((((unsigned) ntohl(si.sin_addr.s_addr)) & 0xFF000000U) ==
	       0x7F000000U) ||
	       (getsockname(s->fd,(struct sockaddr*) &di,&st) ?
	       EPMD_FALSE : si.sin_addr.s_addr == di.sin_addr.s_addr));
      }
      dbg_tty_printf(g,2,(s->local_peer) ? "Local peer connected" :
		     "Non-local peer connected");

      s->want = 0;
      s->got  = 0;
      s->mod_time = current_time(g);

      s->buf = (char *)malloc(INBUF_SIZE);

      if (s->buf == NULL) {
	dbg_printf(g,0,"epmd: Insufficient memory");
	close(fd);
	return EPMD_FALSE;
      }

      dbg_tty_printf(g,2,"opening connection on file descriptor %d",fd);
      return EPMD_TRUE;
    }
  }

  dbg_tty_printf(g,0,"failed opening connection on file descriptor %d",fd);
  close(fd);
  return EPMD_FALSE;
}
