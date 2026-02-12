cmd_directory (const char *com, const char *val, void *place)
{
  char *s, *t;


  if (!cmd_file (com, val, place))
    return false;

  s = *(char **)place;
  t = s + strlen (s);
  while (t > s && *--t == '/')
    *t = '\0';

  return true;
}
