gather_time_entropy(void)
{
#ifdef COMPILING_FOR_WINDOWS
  FILETIME ft;
  GetSystemTimeAsFileTime(&ft);
  return ft.dwHighDateTime ^ ft.dwLowDateTime;
#else
  struct timeval tv;
  int gettimeofday_res;

  gettimeofday_res = gettimeofday(&tv, NULL);
  assert (gettimeofday_res == 0);


  return tv.tv_usec;
#endif
}
