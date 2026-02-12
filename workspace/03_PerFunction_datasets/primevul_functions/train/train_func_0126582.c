read_response_line(smtp_inblock *inblock, uschar *buffer, int size, int timeout)
{
uschar *p = buffer;
uschar *ptr = inblock->ptr;
uschar *ptrend = inblock->ptrend;
client_conn_ctx * cctx = inblock->cctx;


for (;;)
  {
  int rc;


  while (ptr < ptrend)
    {
    int c = *ptr++;
    if (c == '\n')
      {
      while (p > buffer && isspace(p[-1])) p--;
      *p = 0;
      inblock->ptr = ptr;
      return p - buffer;
      }
    *p++ = c;
    if (--size < 4)
      {
      *p = 0;
      errno = ERRNO_SMTPFORMAT;
      return -1;
      }
    }


  if((rc = ip_recv(cctx, inblock->buffer, inblock->buffersize, timeout)) <= 0)
    {
    DEBUG(D_deliver|D_transport|D_acl)
      debug_printf_indent(errno ? "  SMTP(%s)<<\n" : "  SMTP(closed)<<\n",
	strerror(errno));
    break;
    }


  ptrend = inblock->ptrend = inblock->buffer + rc;
  ptr = inblock->buffer;
  DEBUG(D_transport|D_acl) debug_printf_indent("read response data: size=%d\n", rc);
  }


*buffer = 0;
return -1;
}
