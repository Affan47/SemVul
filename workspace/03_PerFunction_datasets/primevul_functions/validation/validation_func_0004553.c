pts_name (int fd, char **pts, size_t buf_len, struct stat64 *stp)
{
  int rv;
  char *buf = *pts;

  for (;;)
    {
      char *new_buf;

      if (buf_len)
	{
	  rv = __ptsname_internal (fd, buf, buf_len, stp);
	  if (rv != 0)
	    {
	      if (rv == ENOTTY)


		rv = EINVAL;
	      errno = rv;
	      break;
	    }

	  if (memchr (buf, '\0', buf_len))

	    break;


	  buf_len += buf_len;
	}
      else

	buf_len = 128;

      if (buf != *pts)

	new_buf = (char *) realloc (buf, buf_len);
      else
	new_buf = (char *) malloc (buf_len);
      if (! new_buf)
	{
	  rv = -1;
	  __set_errno (ENOMEM);
	  break;
	}
      buf = new_buf;
    }

  if (rv == 0)
    *pts = buf;
  else if (buf != *pts)
    free (buf);

  return rv;
}
