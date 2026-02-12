string_dequote(uschar **sptr)
{
uschar *s = *sptr;
uschar *t, *yield;


if (*s != '\"')
  {
  while (*s != 0 && !isspace(*s)) s++;
  }
else
  {
  s++;
  while (*s != 0 && *s != '\"')
    {
    if (*s == '\\') (void)string_interpret_escape(&s);
    s++;
    }
  if (*s != 0) s++;
  }


t = yield = store_get(s - *sptr + 1);
s = *sptr;


if (*s != '\"')
  {
  while (*s != 0 && !isspace(*s)) *t++ = *s++;
  }
else
  {
  s++;
  while (*s != 0 && *s != '\"')
    {
    if (*s == '\\') *t++ = string_interpret_escape(&s);
      else *t++ = *s;
    s++;
    }
  if (*s != 0) s++;
  }


*sptr = s;
*t = 0;
return yield;
}
