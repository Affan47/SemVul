check_user_specified_header (const char *s)
{
  const char *p;

  for (p = s; *p && *p != ':' && !c_isspace (*p); p++)
    ;


  if (*p != ':' || p == s)
    return false;

  if (strchr (s, '\n'))
    return false;
  return true;
}
