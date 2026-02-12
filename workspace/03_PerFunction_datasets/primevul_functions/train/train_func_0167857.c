cmd_file (const char *com _GL_UNUSED, const char *val, void *place)
{
  char **pstring = (char **)place;

  xfree_null (*pstring);


  *pstring = xstrdup (val);

#if defined(WINDOWS) || defined(MSDOS)

  {
    char *s;
    for (s = *pstring; *s; s++)
      if (*s == '\\')
        *s = '/';
  }
#endif
  return true;
}
