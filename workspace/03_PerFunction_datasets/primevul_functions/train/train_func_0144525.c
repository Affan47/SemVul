_gcry_rngcsprng_fast_poll (void)
{
  initialize_basics ();

  lock_pool ();
  if (rndpool)
    {

      do_fast_random_poll ();
    }
  unlock_pool ();
}
