__getlogin_r_loginuid (name, namesize)
     char *name;
     size_t namesize;
{
  int fd = open_not_cancel_2 ("/proc/self/loginuid", O_RDONLY);
  if (fd == -1)
    return -1;


  char uidbuf[12];
  ssize_t n = TEMP_FAILURE_RETRY (read_not_cancel (fd, uidbuf,
						   sizeof (uidbuf)));
  close_not_cancel_no_status (fd);

  uid_t uid;
  char *endp;
  if (n <= 0
      || n == sizeof (uidbuf)
      || (uidbuf[n] = '\0',
	  uid = strtoul (uidbuf, &endp, 10),
	  endp == uidbuf || *endp != '\0'))
    return -1;

  size_t buflen = 1024;
  char *buf = alloca (buflen);
  bool use_malloc = false;
  struct passwd pwd;
  struct passwd *tpwd;
  int result = 0;
  int res;

  while ((res = __getpwuid_r (uid, &pwd, buf, buflen, &tpwd)) == ERANGE)
    if (__libc_use_alloca (2 * buflen))
      buf = extend_alloca (buf, buflen, 2 * buflen);
    else
      {
	buflen *= 2;
	char *newp = realloc (use_malloc ? buf : NULL, buflen);
	if (newp == NULL)
	  {
	    result = ENOMEM;
	    goto out;
	  }
	buf = newp;
	use_malloc = true;
      }

  if (res != 0 || tpwd == NULL)
    {
      result = -1;
      goto out;
    }

  size_t needed = strlen (pwd.pw_name) + 1;
  if (needed > namesize)
    {
      __set_errno (ERANGE);
      result = ERANGE;
      goto out;
    }

  memcpy (name, pwd.pw_name, needed);

 out:
  if (use_malloc)
    free (buf);

  return result;
}
