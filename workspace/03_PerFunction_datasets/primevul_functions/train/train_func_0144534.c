_gcry_rngcsprng_update_seed_file (void)
{
  unsigned long *sp, *dp;
  int fd, i;


  initialize_basics ();
  lock_pool ();

  if ( !seed_file_name || !rndpool || !pool_filled )
    {
      unlock_pool ();
      return;
    }
  if ( !allow_seed_file_update )
    {
      unlock_pool ();
      log_info(_("note: random_seed file not updated\n"));
      return;
    }


  for (i=0,dp=(unsigned long*)(void*)keypool, sp=(unsigned long*)(void*)rndpool;
       i < POOLWORDS; i++, dp++, sp++ )
    {
      *dp = *sp + ADD_VALUE;
    }
  mix_pool(rndpool); rndstats.mixrnd++;
  mix_pool(keypool); rndstats.mixkey++;

#if defined(HAVE_DOSISH_SYSTEM) || defined(__CYGWIN__)
  fd = open (seed_file_name, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,
             S_IRUSR|S_IWUSR );
#else
# if LOCK_SEED_FILE
    fd = open (seed_file_name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR );
# else
    fd = open (seed_file_name, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR );
# endif
#endif

  if (fd == -1 )
    log_info (_("can't create `%s': %s\n"), seed_file_name, strerror(errno) );
  else if (lock_seed_file (fd, seed_file_name, 1))
    {
      close (fd);
    }
#if LOCK_SEED_FILE
  else if (ftruncate (fd, 0))
    {
      log_info(_("can't write `%s': %s\n"), seed_file_name, strerror(errno));
      close (fd);
    }
#endif
  else
    {
      do
        {
          i = write (fd, keypool, POOLSIZE );
        }
      while (i == -1 && errno == EINTR);
      if (i != POOLSIZE)
        log_info (_("can't write `%s': %s\n"),seed_file_name, strerror(errno));
      if (close(fd))
        log_info (_("can't close `%s': %s\n"),seed_file_name, strerror(errno));
    }

  unlock_pool ();
}
