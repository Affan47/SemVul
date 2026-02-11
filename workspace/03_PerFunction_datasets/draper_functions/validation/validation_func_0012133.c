do_fwriteerror (FILE *fp, bool ignore_ebadf)
{

  static bool stdout_closed = false;

  if (fp == stdout)
    {
      if (stdout_closed)
        return 0;


      stdout_closed = true;
    }


  errno = 0;

  if (ferror (fp))
    {
      if (fflush (fp))
        goto close_preserving_errno;


      if (fputc ('\0', fp) == EOF)
        goto close_preserving_errno;
      if (fflush (fp))
        goto close_preserving_errno;

      errno = 0;
      goto close_preserving_errno;
    }

  if (ignore_ebadf)
    {


      if (fflush (fp))
        goto close_preserving_errno;
      if (fclose (fp) && errno != EBADF)
        goto got_errno;
    }
  else
    {
      if (fclose (fp))
        goto got_errno;
    }

  return 0;

 close_preserving_errno:


  {
    int saved_errno = errno;
    fclose (fp);
    errno = saved_errno;
  }
 got_errno:

  if (errno == EPIPE)
    return 0;
  else
    return -1;
}
