transport_write_block_fd(transport_ctx * tctx, uschar *block, int len, BOOL more)
{
int i, rc, save_errno;
int local_timeout = transport_write_timeout;
int fd = tctx->u.fd;


for (i = 0; i < 100; i++)
  {
  DEBUG(D_transport)
    debug_printf("writing data block fd=%d size=%d timeout=%d%s\n",
      fd, len, local_timeout, more ? " (more expected)" : "");


  if (transport_write_timeout <= 0)
    {
    rc =
#ifdef SUPPORT_TLS
	tls_out.active.sock == fd ? tls_write(tls_out.active.tls_ctx, block, len, more) :
#endif
#ifdef MSG_MORE
	more && !(tctx->options & topt_not_socket)
	  ? send(fd, block, len, MSG_MORE) :
#endif
	write(fd, block, len);
    save_errno = errno;
    }


  else
    {
    ALARM(local_timeout);

    rc =
#ifdef SUPPORT_TLS
	tls_out.active.sock == fd ? tls_write(tls_out.active.tls_ctx, block, len, more) :
#endif
#ifdef MSG_MORE
	more && !(tctx->options & topt_not_socket)
	  ? send(fd, block, len, MSG_MORE) :
#endif
	write(fd, block, len);

    save_errno = errno;
    local_timeout = ALARM_CLR(0);
    if (sigalrm_seen)
      {
      errno = ETIMEDOUT;
      return FALSE;
      }
    }


  if (rc == len) { transport_count += len; return TRUE; }


  if (rc >= 0)
    {
    len -= rc;
    block += rc;
    transport_count += rc;
    DEBUG(D_transport) debug_printf("write incomplete (%d)\n", rc);
    goto CHECK_TIMEOUT;
    }


  if (save_errno == EINTR)
    {
    DEBUG(D_transport)
      debug_printf("write interrupted before anything written\n");
    goto CHECK_TIMEOUT;
    }


  if (save_errno == EAGAIN)
    {
    DEBUG(D_transport)
      debug_printf("write temporarily locked out, waiting 1 sec\n");
    sleep(1);


    CHECK_TIMEOUT:
    if (transport_write_timeout > 0 && local_timeout <= 0)
      {
      errno = ETIMEDOUT;
      return FALSE;
      }
    continue;
    }


  DEBUG(D_transport) debug_printf("writing error %d: %s\n", save_errno,
    strerror(save_errno));
  errno = save_errno;
  return FALSE;
  }


errno = ERRNO_WRITEINCOMPLETE;
return FALSE;
}
