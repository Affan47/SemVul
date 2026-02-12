initialize_basics(void)
{
  static int initialized;

  if (!initialized)
    {
      initialized = 1;

#ifdef USE_RANDOM_DAEMON
      _gcry_daemon_initialize_basics ();
#endif


      gcry_assert (GCRY_WEAK_RANDOM == 0
                   && GCRY_STRONG_RANDOM == 1
                   && GCRY_VERY_STRONG_RANDOM == 2);
    }
}
