_gcry_rngcsprng_randomize (void *buffer, size_t length,
                           enum gcry_random_level level)
{
  unsigned char *p;


  initialize ();


  if ( quick_test && level > GCRY_STRONG_RANDOM )
    level = GCRY_STRONG_RANDOM;


  level &= 3;

#ifdef USE_RANDOM_DAEMON
  if (allow_daemon
      && !_gcry_daemon_randomize (daemon_socket_name, buffer, length, level))
    return;
  allow_daemon = 0;
#endif


  lock_pool ();


  if (level >= GCRY_VERY_STRONG_RANDOM)
    {
      rndstats.getbytes2 += length;
      rndstats.ngetbytes2++;
    }
  else
    {
      rndstats.getbytes1 += length;
      rndstats.ngetbytes1++;
    }


  for (p = buffer; length > 0;)
    {
      size_t n;

      n = length > POOLSIZE? POOLSIZE : length;
      read_pool (p, n, level);
      length -= n;
      p += n;
    }


  unlock_pool ();
}
