strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*) s;
  return 0;
}
