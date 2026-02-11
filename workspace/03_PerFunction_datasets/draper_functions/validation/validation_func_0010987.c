getHomeDir() {
#ifdef VMS

  return new GooString("SYS$LOGIN:");

#elif defined(__EMX__) || defined(_WIN32)

  char *s;
  GooString *ret;

  if ((s = getenv("HOME")))
    ret = new GooString(s);
  else
    ret = new GooString(".");
  return ret;

#elif defined(ACORN)

  return new GooString("@");

#elif defined(MACOS)

  return new GooString(":");

#else

  char *s;
  struct passwd *pw;
  GooString *ret;

  if ((s = getenv("HOME"))) {
    ret = new GooString(s);
  } else {
    if ((s = getenv("USER")))
      pw = getpwnam(s);
    else
      pw = getpwuid(getuid());
    if (pw)
      ret = new GooString(pw->pw_dir);
    else
      ret = new GooString(".");
  }
  return ret;
#endif
}
