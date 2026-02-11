gen_tempname (tmpl)
     char *tmpl;
{
  int len;
  char *XXXXXX;
  static uint64_t value;
  uint64_t random_time_bits;
  int count, fd = -1;
  int save_errno = errno;

  len = strlen (tmpl);
  if (len < 6 || strcmp (&tmpl[len - 6], "XXXXXX"))
    {
      __set_errno (EINVAL);
      return -1;
    }


  XXXXXX = &tmpl[len - 6];


#ifdef RANDOM_BITS
  RANDOM_BITS (random_time_bits);
#else
# if HAVE_GETTIMEOFDAY || _LIBC
  {
    struct timeval tv;
    __gettimeofday (&tv, NULL);
    random_time_bits = ((uint64_t) tv.tv_usec << 16) ^ tv.tv_sec;
  }
# else
  random_time_bits = time (NULL);
# endif
#endif
  value += random_time_bits ^ __getpid ();

  for (count = 0; count < TMP_MAX; value += 7777, ++count)
    {
      uint64_t v = value;


      XXXXXX[0] = letters[v % 62];
      v /= 62;
      XXXXXX[1] = letters[v % 62];
      v /= 62;
      XXXXXX[2] = letters[v % 62];
      v /= 62;
      XXXXXX[3] = letters[v % 62];
      v /= 62;
      XXXXXX[4] = letters[v % 62];
      v /= 62;
      XXXXXX[5] = letters[v % 62];

      fd = __mkdir (tmpl, S_IRUSR | S_IWUSR | S_IXUSR);

      if (fd >= 0)
	{
	  __set_errno (save_errno);
	  return fd;
	}
      else if (errno != EEXIST)
	return -1;
    }


  __set_errno (EEXIST);
  return -1;
}
