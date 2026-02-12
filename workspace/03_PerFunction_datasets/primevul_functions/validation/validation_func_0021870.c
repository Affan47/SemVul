mkalldirs (const char *path)
{
  const char *p;
  char *t;
  struct_stat st;
  int res;

  p = path + strlen (path);
  for (; *p != '/' && p != path; p--)
    ;


  if ((p == path) && (*p != '/'))
    return 0;
  t = strdupdelim (path, p);


  if ((stat (t, &st) == 0))
    {
      if (S_ISDIR (st.st_mode))
        {
          xfree (t);
          return 0;
        }
      else
        {


          DEBUGP (("Removing %s because of directory danger!\n", t));
          unlink (t);
        }
    }
  res = make_directory (t);
  if (res != 0)
    logprintf (LOG_NOTQUIET, "%s: %s", t, strerror (errno));
  xfree (t);
  return res;
}
