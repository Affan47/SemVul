cups_swap(unsigned char *buf,
          int           bytes)
{
  unsigned char	even, odd;


  bytes /= 2;

  while (bytes > 0)
  {
    even   = buf[0];
    odd    = buf[1];
    buf[0] = odd;
    buf[1] = even;

    buf += 2;
    bytes --;
  }
}
