smtp_read_response(void * sx0, uschar *buffer, int size, int okdigit,
   int timeout)
{
smtp_context * sx = sx0;
uschar *ptr = buffer;
int count = 0;

errno = 0;

#ifdef EXPERIMENTAL_PIPE_CONNECT
if (sx->pending_BANNER || sx->pending_EHLO)
  if (smtp_reap_early_pipe(sx, &count) != OK)
    {
    DEBUG(D_transport) debug_printf("failed reaping pipelined cmd responsess\n");
    return FALSE;
    }
#endif


for (;;)
  {
  if ((count = read_response_line(&sx->inblock, ptr, size, timeout)) < 0)
    return FALSE;

  HDEBUG(D_transport|D_acl|D_v)
    debug_printf_indent("  %s %s\n", ptr == buffer ? "SMTP<<" : "      ", ptr);


  if (count < 3 ||
     !isdigit(ptr[0]) ||
     !isdigit(ptr[1]) ||
     !isdigit(ptr[2]) ||
     (ptr[3] != '-' && ptr[3] != ' ' && ptr[3] != 0))
    {
    errno = ERRNO_SMTPFORMAT;
    return FALSE;
    }


  if (ptr[3] != '-') break;


  ptr += count;
  *ptr++ = '\n';
  size -= count + 1;
  }

#ifdef TCP_FASTOPEN
  tfo_out_check(sx->cctx.sock);
#endif


errno = 0;
return buffer[0] == okdigit;
}
