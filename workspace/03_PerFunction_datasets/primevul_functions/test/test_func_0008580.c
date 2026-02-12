timespec_cmp(struct timespec time1, struct timespec time2)
{

  if (time1.tv_sec < time2.tv_sec)
    return -1;

  else if (time1.tv_sec > time2.tv_sec)
    return 1;

  else if (time1.tv_nsec < time2.tv_nsec)
    return -1;

  else if (time1.tv_nsec > time2.tv_nsec)
    return 1;

  else
    return 0;
}
