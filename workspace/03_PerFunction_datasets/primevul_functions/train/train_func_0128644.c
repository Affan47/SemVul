update_random_seed_file()
{
    ulong *sp, *dp;
    int fd, i;

    if( !seed_file_name || !is_initialized || !pool_filled )
	return;
    if( !allow_seed_file_update ) {
	log_info(_("note: random_seed file not updated\n"));
	return;
    }


    for(i=0,dp=(ulong*)keypool, sp=(ulong*)rndpool;
				    i < POOLWORDS; i++, dp++, sp++ ) {
	*dp = *sp + ADD_VALUE;
    }
    mix_pool(rndpool); rndstats.mixrnd++;
    mix_pool(keypool); rndstats.mixkey++;

#if defined(HAVE_DOSISH_SYSTEM) || defined(__CYGWIN__)
    fd = open( seed_file_name, O_WRONLY|O_CREAT|O_TRUNC|O_BINARY,
							S_IRUSR|S_IWUSR );
#else
# if LOCK_SEED_FILE
    fd = open( seed_file_name, O_WRONLY|O_CREAT, S_IRUSR|S_IWUSR );
# else
#  ifdef __VMS


    {
        int backoff = 0;

        while ((fd = open( seed_file_name,
                           O_WRONLY|O_CREAT,
                           S_IRUSR|S_IWUSR,
                           "shr=get")) == -1 )
        {
          if ((errno != EVMSERR) || (vaxc$errno != RMS$_FLK))
            {

              log_info (_("can't lock `%s': %s\n"),
                        seed_file_name, strerror (errno));
              return;
            }

          if (backoff > 2)
            log_info( _("waiting for lock on `%s'...\n"), seed_file_name);

          wait_vms( backoff+ 0.25);
          if (backoff < 10)
            backoff++ ;
        }
    }
#  else
    fd = open( seed_file_name, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR );
#  endif
# endif
#endif
    if( fd == -1 ) {
	log_info(_("can't create `%s': %s\n"), seed_file_name, strerror(errno));
	return;
    }

    if (lock_seed_file (fd, seed_file_name, 1))
      {
        close (fd);
        return;
      }
#if LOCK_SEED_FILE
    if (ftruncate (fd, 0))
      {
	log_info(_("can't write `%s': %s\n"), seed_file_name, strerror(errno));
        close (fd);
        return;
      }
#endif

    do {
	i = write( fd, keypool, POOLSIZE );
    } while( i == -1 && errno == EINTR );
    if( i != POOLSIZE ) {
	log_info(_("can't write `%s': %s\n"), seed_file_name, strerror(errno) );
    }
    if( close(fd) )
	log_info(_("can't close `%s': %s\n"), seed_file_name, strerror(errno) );
}
