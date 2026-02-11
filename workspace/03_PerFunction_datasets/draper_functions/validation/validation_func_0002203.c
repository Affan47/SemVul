send (ACE_HANDLE handle, size_t n, ...)
{
  va_list argp;
  int total_tuples = static_cast<int> (n / 2);
  iovec *iovp;
#if defined (ACE_HAS_ALLOCA)
  iovp = (iovec *) alloca (total_tuples * sizeof (iovec));
#else
  ACE_NEW_RETURN (iovp,
                  iovec[total_tuples],
                  -1);
#endif

  va_start (argp, n);

  for (int i = 0; i < total_tuples; i++)
    {
      iovp[i].iov_base = va_arg (argp, char *);
      iovp[i].iov_len = va_arg (argp, int);
    }

  ssize_t result = ACE_OS::sendv (handle, iovp, total_tuples);
#if !defined (ACE_HAS_ALLOCA)
  delete [] iovp;
#endif
  va_end (argp);
  return result;
}
