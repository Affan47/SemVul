_gcry_rngcsprng_use_daemon (int onoff)
{
#ifdef USE_RANDOM_DAEMON
  int last;


  last = allow_daemon;
  if (onoff != -1)
    allow_daemon = onoff;

  return last;
#else
  (void)onoff;
  return 0;
#endif
}
