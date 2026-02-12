do_fast_random_poll (void)
{
  gcry_assert (pool_is_locked);

  rndstats.fastpolls++;

  if (fast_gather_fnc)
    fast_gather_fnc (add_randomness, RANDOM_ORIGIN_FASTPOLL);


#if HAVE_GETHRTIME
  {
    hrtime_t tv;
    tv = gethrtime();
    add_randomness( &tv, sizeof(tv), RANDOM_ORIGIN_FASTPOLL );
  }
#elif HAVE_GETTIMEOFDAY
  {
    struct timeval tv;
    if( gettimeofday( &tv, NULL ) )
      BUG();
    add_randomness( &tv.tv_sec, sizeof(tv.tv_sec), RANDOM_ORIGIN_FASTPOLL );
    add_randomness( &tv.tv_usec, sizeof(tv.tv_usec), RANDOM_ORIGIN_FASTPOLL );
  }
#elif HAVE_CLOCK_GETTIME
  {	struct timespec tv;
  if( clock_gettime( CLOCK_REALTIME, &tv ) == -1 )
    BUG();
  add_randomness( &tv.tv_sec, sizeof(tv.tv_sec), RANDOM_ORIGIN_FASTPOLL );
  add_randomness( &tv.tv_nsec, sizeof(tv.tv_nsec), RANDOM_ORIGIN_FASTPOLL );
  }
#else
# ifndef HAVE_DOSISH_SYSTEM
  {	struct tms buf;
  times( &buf );
  add_randomness( &buf, sizeof buf, RANDOM_ORIGIN_FASTPOLL );
  }
# endif
#endif

#ifdef HAVE_GETRUSAGE
# ifdef RUSAGE_SELF
  {
    struct rusage buf;


    getrusage (RUSAGE_SELF, &buf );
    add_randomness( &buf, sizeof buf, RANDOM_ORIGIN_FASTPOLL );
    memset( &buf, 0, sizeof buf );
  }
# else
#  ifdef __GCC__
#   warning There is no RUSAGE_SELF on this system
#  endif
# endif
#endif


  {
    time_t x = time(NULL);
    add_randomness( &x, sizeof(x), RANDOM_ORIGIN_FASTPOLL );
  }
  {
    clock_t x = clock();
    add_randomness( &x, sizeof(x), RANDOM_ORIGIN_FASTPOLL );
  }


  _gcry_rndhw_poll_fast (add_randomness, RANDOM_ORIGIN_FASTPOLL);
}
