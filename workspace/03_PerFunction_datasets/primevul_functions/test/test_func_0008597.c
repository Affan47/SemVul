clock_gettime_with_res(clockid_t clock_id, struct timespec *tp, struct timespec *res)
{
  int ret;

  if ((!tp) || (!res))
    return -1;

  ret = clock_gettime(clock_id, tp);

  if (ret == 0 && res->tv_nsec > 1)
    tp->tv_nsec = (tp->tv_nsec/res->tv_nsec)*res->tv_nsec;

  return ret;
}
