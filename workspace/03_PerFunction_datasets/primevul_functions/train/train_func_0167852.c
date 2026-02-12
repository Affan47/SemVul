dehyphen (char *s)
{
  char *t = s;
  char *h = s;
  while (*h)
    if (*h == '_' || *h == '-')
      ++h;
    else
      *t++ = *h++;
  *t = '\0';
}
