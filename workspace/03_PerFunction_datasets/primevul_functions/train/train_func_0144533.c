initialize(void)
{


  initialize_basics ();


  lock_pool ();
  if (!rndpool)
    {


      rndpool = (secure_alloc
                 ? xcalloc_secure (1, POOLSIZE + BLOCKLEN)
                 : xcalloc (1, POOLSIZE + BLOCKLEN));
      keypool = (secure_alloc
                 ? xcalloc_secure (1, POOLSIZE + BLOCKLEN)
                 : xcalloc (1, POOLSIZE + BLOCKLEN));


      slow_gather_fnc = getfnc_gather_random ();


      fast_gather_fnc = getfnc_fast_random_poll ();

    }
  unlock_pool ();
}
