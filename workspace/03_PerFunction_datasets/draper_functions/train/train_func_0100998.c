do_bin2hex (const void *buffer, size_t length, char *stringbuf, int with_colon)
{
  const unsigned char *s;
  char *p;

  if (!stringbuf)
    {


      size_t n = with_colon? 3:2;
      size_t nbytes = n * length + 1;
      if (length &&  (nbytes-1) / n != length)
        {
          errno = ENOMEM;
          return NULL;
        }
      stringbuf = xtrymalloc (nbytes);
      if (!stringbuf)
        return NULL;
    }

  for (s = buffer, p = stringbuf; length; length--, s++)
    {
      if (with_colon && s != buffer)
        *p++ = ':';
      *p++ = tohex ((*s>>4)&15);
      *p++ = tohex (*s&15);
    }
  *p = 0;

  return stringbuf;
}
