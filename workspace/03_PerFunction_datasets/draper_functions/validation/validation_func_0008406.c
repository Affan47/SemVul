getElapsed()
{
  double total;
  struct timeval elapsed;

  if (active)
    gettimeofday(&end_time, NULL);

  if (start_time.tv_usec > end_time.tv_usec) {
      end_time.tv_usec += USEC_PER_SEC;
      end_time.tv_sec--;
  }

  elapsed.tv_usec = end_time.tv_usec - start_time.tv_usec;
  elapsed.tv_sec = end_time.tv_sec - start_time.tv_sec;

  total = elapsed.tv_sec + ((double) elapsed.tv_usec / 1e6);
  if (total < 0)
      total = 0;

  return total;
}
