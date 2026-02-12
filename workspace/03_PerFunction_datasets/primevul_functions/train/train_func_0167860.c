home_dir (void)
{
  static char *buf = NULL;
  static char *home, *ret;

  if (!home)
    {
      home = getenv ("HOME");
      if (!home)
        {
#if defined(MSDOS)
          int len;


          const char *_w32_get_argv0 (void);
          char *p;

          buff = _w32_get_argv0 ();

          p = strrchr (buf, '/');
          if (!p)
            p = strrchr (buf, '\\');
          assert (p);

          len = p - buff + 1;
          buff = strdup (_w32_get_argv0 ());

          home = buf;
#elif !defined(WINDOWS)


          struct passwd *pwd = getpwuid (getuid ());
          if (!pwd || !pwd->pw_dir)
            return NULL;
          home = pwd->pw_dir;
#else


          home = ws_mypath ();
#endif
        }
    }

  ret = home ? xstrdup (home) : NULL;
  free (buf);

  return ret;
}
