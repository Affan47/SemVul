lmtp_read_response(FILE *f, uschar *buffer, int size, int okdigit, int timeout)
{
int count;
uschar *ptr = buffer;
uschar *readptr = buffer;


errno = 0;


for (;;)
  {


  if (size < 10)
    {
    *readptr = 0;
    errno = ERRNO_SMTPFORMAT;
    return FALSE;
    }


  for (;;)
    {
    char *rc;
    int save_errno;

    *readptr = 0;
    sigalrm_seen = FALSE;
    ALARM(timeout);
    rc = Ufgets(readptr, size-1, f);
    save_errno = errno;
    ALARM_CLR(0);
    errno = save_errno;

    if (rc != NULL) break;


    if (sigalrm_seen) errno = ETIMEDOUT;


    else if (errno == EINTR)
      {
      DEBUG(D_transport) debug_printf("EINTR while reading LMTP response\n");
      continue;
      }


    buffer[0] = 0;
    return FALSE;
    }


  count = Ustrlen(readptr);
  size -= count;
  count += readptr - ptr;


  if (ptr[count-1] != '\n')
    {
    DEBUG(D_transport)
      {
      int i;
      debug_printf("LMTP input line incomplete in one buffer:\n  ");
      for (i = 0; i < count; i++)
        {
        int c = (ptr[i]);
        if (mac_isprint(c)) debug_printf("%c", c); else debug_printf("<%d>", c);
        }
      debug_printf("\n");
      }
    readptr = ptr + count;
    continue;
    }


  while (count > 0 && isspace(ptr[count-1])) count--;
  ptr[count] = 0;

  DEBUG(D_transport|D_v)
    {
    uschar *s = ptr;
    uschar *t = ptr;
    while (*t != 0)
      {
      while (*t != 0 && *t != '\n') t++;
      debug_printf("  %s %*s\n", (s == ptr)? "LMTP<<" : "      ",
        (int)(t-s), s);
      if (*t == 0) break;
      s = t = t + 1;
      }
    }


  for(;;)
    {
    uschar *p;
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


    p = ptr + 3;
    while (*(++p) != 0)
      {
      if (*p == '\n')
        {
        ptr = ++p;
        break;
        }
      }
    if (*p == 0) break;
    }


  if (ptr[3] != '-') break;


  ptr += count;
  *ptr++ = '\n';
  size--;
  readptr = ptr;
  }


errno = 0;
return buffer[0] == okdigit;
}
