deliver_local(address_item *addr, BOOL shadowing)
{
BOOL use_initgroups;
uid_t uid;
gid_t gid;
int status, len, rc;
int pfd[2];
pid_t pid;
uschar *working_directory;
address_item *addr2;
transport_instance *tp = addr->transport;


if(addr->prop.errors_address)
  return_path = addr->prop.errors_address;
#ifdef EXPERIMENTAL_SRS
else if (addr->prop.srs_sender)
  return_path = addr->prop.srs_sender;
#endif
else
  return_path = sender_address;

if (tp->return_path)
  {
  uschar *new_return_path = expand_string(tp->return_path);
  if (!new_return_path)
    {
    if (!expand_string_forcedfail)
      {
      common_error(TRUE, addr, ERRNO_EXPANDFAIL,
        US"Failed to expand return path \"%s\" in %s transport: %s",
        tp->return_path, tp->name, expand_string_message);
      return;
      }
    }
  else return_path = new_return_path;
  }


used_return_path = return_path;


if (!findugid(addr, tp, &uid, &gid, &use_initgroups)) return;


if (  (deliver_home = tp->home_dir)
   || (  (deliver_home = addr->home_dir)
      && !testflag(addr, af_home_expanded)
   )  )
  {
  uschar *rawhome = deliver_home;
  deliver_home = NULL;
  if (!(deliver_home = expand_string(rawhome)))
    {
    common_error(TRUE, addr, ERRNO_EXPANDFAIL, US"home directory \"%s\" failed "
      "to expand for %s transport: %s", rawhome, tp->name,
      expand_string_message);
    return;
    }
  if (*deliver_home != '/')
    {
    common_error(TRUE, addr, ERRNO_NOTABSOLUTE, US"home directory path \"%s\" "
      "is not absolute for %s transport", deliver_home, tp->name);
    return;
    }
  }


working_directory = tp->current_dir ? tp->current_dir : addr->current_dir;
if (working_directory)
  {
  uschar *raw = working_directory;
  if (!(working_directory = expand_string(raw)))
    {
    common_error(TRUE, addr, ERRNO_EXPANDFAIL, US"current directory \"%s\" "
      "failed to expand for %s transport: %s", raw, tp->name,
      expand_string_message);
    return;
    }
  if (*working_directory != '/')
    {
    common_error(TRUE, addr, ERRNO_NOTABSOLUTE, US"current directory path "
      "\"%s\" is not absolute for %s transport", working_directory, tp->name);
    return;
    }
  }
else working_directory = deliver_home ? deliver_home : US"/";


if (  !shadowing
   && (  tp->return_output || tp->return_fail_output
      || tp->log_output || tp->log_fail_output || tp->log_defer_output
   )  )
  {
  uschar * error;

  addr->return_filename =
    spool_fname(US"msglog", message_subdir, message_id,
      string_sprintf("-%d-%d", getpid(), return_count++));

  if ((addr->return_file = open_msglog_file(addr->return_filename, 0400, &error)) < 0)
    {
    common_error(TRUE, addr, errno, US"Unable to %s file for %s transport "
      "to return message: %s", error, tp->name, strerror(errno));
    return;
    }
  }


if (pipe(pfd) != 0)
  {
  common_error(TRUE, addr, ERRNO_PIPEFAIL, US"Creation of pipe failed: %s",
    strerror(errno));
  return;
  }


search_tidyup();

if ((pid = fork()) == 0)
  {
  BOOL replicate = TRUE;


#ifdef RLIMIT_CORE
  struct rlimit rl;
  rl.rlim_cur = 0;
  rl.rlim_max = 0;
  if (setrlimit(RLIMIT_CORE, &rl) < 0)
    {
# ifdef SETRLIMIT_NOT_SUPPORTED
    if (errno != ENOSYS && errno != ENOTSUP)
# endif
      log_write(0, LOG_MAIN|LOG_PANIC, "setrlimit(RLIMIT_CORE) failed: %s",
        strerror(errno));
    }
#endif


  random_seed = 0;


  if (addr->transport->setup)
    switch((addr->transport->setup)(addr->transport, addr, NULL, uid, gid,
           &(addr->message)))
      {
      case DEFER:
	addr->transport_return = DEFER;
	goto PASS_BACK;

      case FAIL:
	addr->transport_return = PANIC;
	goto PASS_BACK;
      }


  signal(SIGINT, SIG_IGN);
  signal(SIGTERM, SIG_IGN);
  signal(SIGUSR1, SIG_IGN);


  (void)close(pfd[pipe_read]);
  (void)fcntl(pfd[pipe_write], F_SETFD, fcntl(pfd[pipe_write], F_GETFD) |
    FD_CLOEXEC);
  exim_setugid(uid, gid, use_initgroups,
    string_sprintf("local delivery to %s <%s> transport=%s", addr->local_part,
      addr->address, addr->transport->name));

  DEBUG(D_deliver)
    {
    address_item *batched;
    debug_printf("  home=%s current=%s\n", deliver_home, working_directory);
    for (batched = addr->next; batched; batched = batched->next)
      debug_printf("additional batched address: %s\n", batched->address);
    }


  if (Uchdir(working_directory) < 0)
    {
    addr->transport_return = DEFER;
    addr->basic_errno = errno;
    addr->message = string_sprintf("failed to chdir to %s", working_directory);
    }


  else
    {
    BOOL ok = TRUE;
    set_process_info("delivering %s to %s using %s", message_id,
     addr->local_part, addr->transport->name);


    transport_name = addr->transport->name;


    if (addr->transport->filter_command)
      {
      ok = transport_set_up_command(&transport_filter_argv,
        addr->transport->filter_command,
        TRUE, PANIC, addr, US"transport filter", NULL);
      transport_filter_timeout = addr->transport->filter_timeout;
      }
    else transport_filter_argv = NULL;

    if (ok)
      {
      debug_print_string(addr->transport->debug_string);
      replicate = !(addr->transport->info->code)(addr->transport, addr);
      }
    }


  PASS_BACK:

  if (replicate) replicate_status(addr);
  for (addr2 = addr; addr2; addr2 = addr2->next)
    {
    int i;
    int local_part_length = Ustrlen(addr2->local_part);
    uschar *s;
    int ret;

    if(  (ret = write(pfd[pipe_write], &addr2->transport_return, sizeof(int))) != sizeof(int)
      || (ret = write(pfd[pipe_write], &transport_count, sizeof(transport_count))) != sizeof(transport_count)
      || (ret = write(pfd[pipe_write], &addr2->flags, sizeof(addr2->flags))) != sizeof(addr2->flags)
      || (ret = write(pfd[pipe_write], &addr2->basic_errno,    sizeof(int))) != sizeof(int)
      || (ret = write(pfd[pipe_write], &addr2->more_errno,     sizeof(int))) != sizeof(int)
      || (ret = write(pfd[pipe_write], &addr2->delivery_usec,  sizeof(int))) != sizeof(int)
      || (ret = write(pfd[pipe_write], &addr2->special_action, sizeof(int))) != sizeof(int)
      || (ret = write(pfd[pipe_write], &addr2->transport,
        sizeof(transport_instance *))) != sizeof(transport_instance *)


      || (testflag(addr2, af_file)
          && (  (ret = write(pfd[pipe_write], &local_part_length, sizeof(int))) != sizeof(int)
             || (ret = write(pfd[pipe_write], addr2->local_part, local_part_length)) != local_part_length
	     )
	 )
      )
      log_write(0, LOG_MAIN|LOG_PANIC, "Failed writing transport results to pipe: %s",
	ret == -1 ? strerror(errno) : "short write");


    for (i = 0, s = addr2->message; i < 2; i++, s = addr2->user_message)
      {
      int message_length = s ? Ustrlen(s) + 1 : 0;
      if(  (ret = write(pfd[pipe_write], &message_length, sizeof(int))) != sizeof(int)
        || message_length > 0  && (ret = write(pfd[pipe_write], s, message_length)) != message_length
	)
        log_write(0, LOG_MAIN|LOG_PANIC, "Failed writing transport results to pipe: %s",
	  ret == -1 ? strerror(errno) : "short write");
      }
    }


  (void)close(pfd[pipe_write]);
  search_tidyup();
  exit(EXIT_SUCCESS);
  }


if (pid < 0)
  log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Fork failed for local delivery to %s",
    addr->address);


(void)close(pfd[pipe_write]);

for (addr2 = addr; addr2; addr2 = addr2->next)
  {
  if ((len = read(pfd[pipe_read], &status, sizeof(int))) > 0)
    {
    int i;
    uschar **sptr;

    addr2->transport_return = status;
    len = read(pfd[pipe_read], &transport_count,
      sizeof(transport_count));
    len = read(pfd[pipe_read], &addr2->flags, sizeof(addr2->flags));
    len = read(pfd[pipe_read], &addr2->basic_errno,    sizeof(int));
    len = read(pfd[pipe_read], &addr2->more_errno,     sizeof(int));
    len = read(pfd[pipe_read], &addr2->delivery_usec,  sizeof(int));
    len = read(pfd[pipe_read], &addr2->special_action, sizeof(int));
    len = read(pfd[pipe_read], &addr2->transport,
      sizeof(transport_instance *));

    if (testflag(addr2, af_file))
      {
      int llen;
      if (  read(pfd[pipe_read], &llen, sizeof(int)) != sizeof(int)
	 || llen > 64*4
         )
	{
	log_write(0, LOG_MAIN|LOG_PANIC, "bad local_part length read"
	  " from delivery subprocess");
	break;
	}


      if (read(pfd[pipe_read], big_buffer, llen) != llen)
	{
	log_write(0, LOG_MAIN|LOG_PANIC, "bad local_part read"
	  " from delivery subprocess");
	break;
	}
      big_buffer[llen] = 0;
      addr2->local_part = string_copy(big_buffer);
      }

    for (i = 0, sptr = &addr2->message; i < 2; i++, sptr = &addr2->user_message)
      {
      int message_length;
      len = read(pfd[pipe_read], &message_length, sizeof(int));
      if (message_length > 0)
        {
        len = read(pfd[pipe_read], big_buffer, message_length);
	big_buffer[big_buffer_size-1] = '\0';
        if (len > 0) *sptr = string_copy(big_buffer);
        }
      }
    }

  else
    {
    log_write(0, LOG_MAIN|LOG_PANIC, "failed to read delivery status for %s "
      "from delivery subprocess", addr2->unique);
    break;
    }
  }

(void)close(pfd[pipe_read]);


if (!shadowing)
  {
  for (addr2 = addr; addr2; addr2 = addr2->next)
    if (addr2->transport_return == OK)
      {
      if (testflag(addr2, af_homonym))
	sprintf(CS big_buffer, "%.500s/%s\n", addr2->unique + 3, tp->name);
      else
	sprintf(CS big_buffer, "%.500s\n", addr2->unique);


      if (running_in_test_harness) millisleep(300);

      DEBUG(D_deliver) debug_printf("journalling %s", big_buffer);
      len = Ustrlen(big_buffer);
      if (write(journal_fd, big_buffer, len) != len)
	log_write(0, LOG_MAIN|LOG_PANIC, "failed to update journal for %s: %s",
	  big_buffer, strerror(errno));
      }


  if (EXIMfsync(journal_fd) < 0)
    log_write(0, LOG_MAIN|LOG_PANIC, "failed to fsync journal: %s",
      strerror(errno));
  }


while ((rc = wait(&status)) != pid)
  if (rc < 0 && errno == ECHILD)
    {
    log_write(0, LOG_MAIN, "%s transport process vanished unexpectedly",
      addr->transport->driver_name);
    status = 0;
    break;
    }

if ((status & 0xffff) != 0)
  {
  int msb = (status >> 8) & 255;
  int lsb = status & 255;
  int code = (msb == 0)? (lsb & 0x7f) : msb;
  if (msb != 0 || (code != SIGTERM && code != SIGKILL && code != SIGQUIT))
    addr->special_action = SPECIAL_FREEZE;
  log_write(0, LOG_MAIN|LOG_PANIC, "%s transport process returned non-zero "
    "status 0x%04x: %s %d",
    addr->transport->driver_name,
    status,
    msb == 0 ? "terminated by signal" : "exit code",
    code);
  }


if (addr->special_action == SPECIAL_WARN && addr->transport->warn_message)
  {
  int fd;
  uschar *warn_message;
  pid_t pid;

  DEBUG(D_deliver) debug_printf("Warning message requested by transport\n");

  if (!(warn_message = expand_string(addr->transport->warn_message)))
    log_write(0, LOG_MAIN|LOG_PANIC, "Failed to expand \"%s\" (warning "
      "message for %s transport): %s", addr->transport->warn_message,
      addr->transport->name, expand_string_message);

  else if ((pid = child_open_exim(&fd)) > 0)
    {
    FILE *f = fdopen(fd, "wb");
    if (errors_reply_to && !contains_header(US"Reply-To", warn_message))
      fprintf(f, "Reply-To: %s\n", errors_reply_to);
    fprintf(f, "Auto-Submitted: auto-replied\n");
    if (!contains_header(US"From", warn_message))
      moan_write_from(f);
    fprintf(f, "%s", CS warn_message);


    (void)fclose(f);
    (void)child_close(pid, 0);
    }

  addr->special_action = SPECIAL_NONE;
  }
}
