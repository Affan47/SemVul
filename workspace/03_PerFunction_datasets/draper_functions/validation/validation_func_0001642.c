copy_string(unsigned char *c, unsigned char *s)
{
  int i;
  c = c + 5;
  for (i = 0; (i < 13 && *c != 0x0A); i++)
    *(s++) = *(c++);
  *s = 0;
  while (i-- && (*--s == 0x20)) *s = 0;
}
