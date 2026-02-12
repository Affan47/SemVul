string_is_ip_address(uschar *s, int *maskptr)
{
int i;
int yield = 4;


if (maskptr != NULL)
  {
  uschar *ss = s + Ustrlen(s);
  *maskptr = 0;
  if (s != ss && isdigit(*(--ss)))
    {
    while (ss > s && isdigit(ss[-1])) ss--;
    if (ss > s && *(--ss) == '/') *maskptr = ss - s;
    }
  }


if (Ustrchr(s, ':') != NULL)
  {
  BOOL had_double_colon = FALSE;
  BOOL v4end = FALSE;
  int count = 0;

  yield = 6;


  if (*s == ':' && *(++s) != ':') return 0;


  for (count = 0; count < 8; count++)
    {


    if (*s == 0 || *s == '%' || *s == '/') return had_double_colon? yield : 0;


    if (*s == ':')
      {
      if (had_double_colon) return 0;
      had_double_colon = TRUE;
      s++;
      continue;
      }


    if (Ustrchr(s, ':') == NULL && Ustrchr(s, '.') != NULL)
      {
      if ((!had_double_colon && count != 6) ||
          (had_double_colon && count > 6)) return 0;
      v4end = TRUE;
      yield = 6;
      break;
      }


    if (!isxdigit(*s++)) return 0;
    if (isxdigit(*s) && isxdigit(*(++s)) && isxdigit(*(++s))) s++;


    if (*s == ':' && *(++s) == 0) return 0;
    }


  if (!v4end)
    return (*s == 0 || *s == '%' ||
           (*s == '/' && maskptr != NULL && *maskptr != 0))? yield : 0;
  }


for (i = 0; i < 4; i++)
  {
  if (i != 0 && *s++ != '.') return 0;
  if (!isdigit(*s++)) return 0;
  if (isdigit(*s) && isdigit(*(++s))) s++;
  }

return (*s == 0 || (*s == '/' && maskptr != NULL && *maskptr != 0))?
  yield : 0;
}
