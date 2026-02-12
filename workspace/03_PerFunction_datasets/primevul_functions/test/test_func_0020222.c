wdequote_pathname (pathname)
     char *pathname;
{
  mbstate_t ps;
  size_t len, n;
  wchar_t *wpathname;
  int i, j;
  wchar_t *orig_wpathname;

  if (mbsmbchar (pathname) == 0)
    {
      udequote_pathname (pathname);
      return;
    }

  len = strlen (pathname);

  n = xdupmbstowcs (&wpathname, NULL, pathname);
  if (n == (size_t) -1)
    {

      udequote_pathname (pathname);
      return;
    }
  orig_wpathname = wpathname;

  for (i = j = 0; wpathname && wpathname[i]; )
    {
      if (wpathname[i] == L'\\')
	i++;

      wpathname[j++] = wpathname[i++];

      if (wpathname[i - 1] == L'\0')
	break;
    }
  if (wpathname)
    wpathname[j] = L'\0';


  memset (&ps, '\0', sizeof(mbstate_t));
  n = wcsrtombs(pathname, (const wchar_t **)&wpathname, len, &ps);
  pathname[len] = '\0';


  free (orig_wpathname);
}
