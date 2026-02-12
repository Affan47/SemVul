swallow_until_crlf(int fd, uschar *base, int already, int capacity)
{
uschar *to = base + already;
uschar *cr;
int have = 0;
int ret;
int last = 0;


cr = memchr(base, '\r', already);
if (cr != NULL)
  {
  if ((cr - base) < already - 1)
    {


    return 0;
    }

  last = 1;
  }

while (capacity > 0)
  {
  do { ret = recv(fd, to, 1, 0); } while (ret == -1 && errno == EINTR);
  if (ret == -1)
    return -1;
  have++;
  if (last)
    return have;
  if (*to == '\r')
    last = 1;
  capacity--;
  to++;
  }


errno = EOVERFLOW;
return -1;
}
