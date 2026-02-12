main_apphead_string (const char* x)
{
  const char *y;

  if (x == NULL) { return ""; }

  if (strcmp (x, "/dev/stdin") == 0 ||
      strcmp (x, "/dev/stdout") == 0 ||
      strcmp (x, "/dev/stderr") == 0) { return "-"; }


  return (y = strrchr (x, '/')) == NULL ? x : y + 1;
}
