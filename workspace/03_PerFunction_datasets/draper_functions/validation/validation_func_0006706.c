_rl_get_char_len (src, ps)
     char *src;
     mbstate_t *ps;
{
  size_t tmp;

  tmp = mbrlen((const char *)src, (size_t)strlen (src), ps);
  if (tmp == (size_t)(-2))
    {

      if (ps)
	memset (ps, 0, sizeof(mbstate_t));
      return -2;
    }
  else if (tmp == (size_t)(-1))
    {


      if (ps)
	memset (ps, 0, sizeof(mbstate_t));
      return -1;
    }
  else if (tmp == (size_t)0)
    return 0;
  else
    return (int)tmp;
}
