static void hp_trunc_time(struct timeval *tv, uint64_t intr) {
  uint64_t time_in_micro;


  time_in_micro = (tv->tv_sec * 1000000) + tv->tv_usec;
  time_in_micro /= intr;
  time_in_micro *= intr;


  tv->tv_sec  = (time_in_micro / 1000000);
  tv->tv_usec = (time_in_micro % 1000000);
}
