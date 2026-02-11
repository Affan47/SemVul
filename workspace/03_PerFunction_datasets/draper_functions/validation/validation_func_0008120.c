allwrite(op,fd,buf,len)
register int (*op)();
register int fd;
register char *buf;
register int len;
{
  register int w;

  while (len) {
    w = op(fd,buf,len);
    if (w == -1) {
      if (errno == error_intr) continue;
      return -1;
    }
    if (w == 0) ;
    buf += w;
    len -= w;
  }
  return 0;
}
