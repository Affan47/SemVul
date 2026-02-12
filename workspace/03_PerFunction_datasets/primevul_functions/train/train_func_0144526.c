read_pool (byte *buffer, size_t length, int level)
{
  int i;
  unsigned long *sp, *dp;


  static volatile pid_t my_pid = (pid_t)(-1);
  volatile pid_t my_pid2;

  gcry_assert (pool_is_locked);

 retry:

  my_pid2 = getpid ();
  if (my_pid == (pid_t)(-1))
    my_pid = my_pid2;
  if ( my_pid != my_pid2 )
    {


      pid_t x;

      my_pid = my_pid2;
      x = my_pid;
      add_randomness (&x, sizeof(x), RANDOM_ORIGIN_INIT);
      just_mixed = 0;
    }

  gcry_assert (pool_is_locked);


  if (length > POOLSIZE)
    {
      log_bug("too many random bits requested\n");
    }

  if (!pool_filled)
    {
      if (read_seed_file() )
        pool_filled = 1;
    }


  if (level == GCRY_VERY_STRONG_RANDOM && !did_initial_extra_seeding)
    {
      size_t needed;

      pool_balance = 0;
      needed = length - pool_balance;
      if (needed < 16)
        needed = 16;
      else if( needed > POOLSIZE )
        BUG ();
      read_random_source (RANDOM_ORIGIN_EXTRAPOLL, needed,
                          GCRY_VERY_STRONG_RANDOM);
      pool_balance += needed;
      did_initial_extra_seeding = 1;
    }


  if (level == GCRY_VERY_STRONG_RANDOM && pool_balance < length)
    {
      size_t needed;

      if (pool_balance < 0)
        pool_balance = 0;
      needed = length - pool_balance;
      if (needed > POOLSIZE)
        BUG ();
      read_random_source (RANDOM_ORIGIN_EXTRAPOLL, needed,
                          GCRY_VERY_STRONG_RANDOM);
      pool_balance += needed;
    }


  while (!pool_filled)
    random_poll();


  do_fast_random_poll();


  {
    pid_t apid = my_pid;
    add_randomness (&apid, sizeof (apid), RANDOM_ORIGIN_INIT);
  }


  if (!just_mixed)
    {
      mix_pool(rndpool);
      rndstats.mixrnd++;
    }


  for(i=0,dp=(unsigned long*)(void*)keypool, sp=(unsigned long*)(void*)rndpool;
      i < POOLWORDS; i++, dp++, sp++ )
    *dp = *sp + ADD_VALUE;


  mix_pool(rndpool); rndstats.mixrnd++;
  mix_pool(keypool); rndstats.mixkey++;


  while (length--)
    {
      *buffer++ = keypool[pool_readpos++];
      if (pool_readpos >= POOLSIZE)
        pool_readpos = 0;
      pool_balance--;
    }

  if (pool_balance < 0)
    pool_balance = 0;


  memset (keypool, 0, POOLSIZE);


  if ( getpid () != my_pid2 )
    {
      pid_t x = getpid();
      add_randomness (&x, sizeof(x), RANDOM_ORIGIN_INIT);
      just_mixed = 0;
      my_pid = x;
      goto retry;
    }
}
