my_strcasecmp_mb(CHARSET_INFO * cs,const char *s, const char *t)
{
  register uint32 l;
  register uchar *map=cs->to_upper;

  while (*s && *t)
  {

    if ((l=my_ismbchar(cs, s, s + cs->mbmaxlen)))
    {
      while (l--)
        if (*s++ != *t++)
          return 1;
    }
    else if (my_mbcharlen(cs, *t) > 1)
      return 1;
    else if (map[(uchar) *s++] != map[(uchar) *t++])
      return 1;
  }

  return (*t != *s);
}
