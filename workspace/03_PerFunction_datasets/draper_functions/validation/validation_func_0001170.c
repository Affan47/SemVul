_dmalloc_open_log(void)
{
  char	log_path[1024];
  int	len;


  if (outfile_fd >= 0
      || dmalloc_logpath == NULL) {
    return;
  }

  build_logfile_path(log_path, sizeof(log_path));


  outfile_fd = open(log_path, O_WRONLY | O_CREAT | O_TRUNC, 0666);
  if (outfile_fd < 0) {

    len = loc_snprintf(error_str, sizeof(error_str),
		       "debug-malloc library: could not open '%s'\r\n",
		       log_path);
    (void)write(STDERR, error_str, len);

    dmalloc_logpath = NULL;
    return;
  }


  dmalloc_message("Dmalloc version '%s' from '%s'",
		  dmalloc_version, DMALLOC_HOME);
  dmalloc_message("flags = %#x, logfile '%s'", _dmalloc_flags, log_path);
  dmalloc_message("interval = %lu, addr = %#lx, seen # = %ld, limit = %ld",
		  _dmalloc_check_interval, (unsigned long)_dmalloc_address,
		  _dmalloc_address_seen_n, _dmalloc_memory_limit);
#if LOCK_THREADS
  dmalloc_message("threads enabled, lock-on = %d, lock-init = %d",
		  _dmalloc_lock_on, THREAD_INIT_LOCK);
#endif

#if LOG_PNT_TIMEVAL
  {
    char	time_buf[64];
    dmalloc_message("starting time = %s",
		     _dmalloc_ptimeval(&_dmalloc_start, time_buf,
				       sizeof(time_buf), 0));
  }
#else
#if HAVE_TIME
  {
    char	time_buf[64];
    dmalloc_message("starting time = %s",
		     _dmalloc_ptime(&_dmalloc_start, time_buf,
				    sizeof(time_buf), 0));
  }
#endif
#endif

#if HAVE_GETPID
  {

    long	our_pid = getpid();

    dmalloc_message("process pid = %ld", our_pid);
  }
#endif
}
