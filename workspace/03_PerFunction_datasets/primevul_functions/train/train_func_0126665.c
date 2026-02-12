par_wait(void)
{
int poffset, status;
address_item *addr, *addrlist;
pid_t pid;

set_process_info("delivering %s: waiting for a remote delivery subprocess "
  "to finish", message_id);


for (;;)
  {
  while ((pid = waitpid(-1, &status, WNOHANG)) <= 0)
    {
    struct timeval tv;
    fd_set select_pipes;
    int maxpipe, readycount;


    if (pid < 0)
      {
      if (errno != ECHILD) continue;

      DEBUG(D_deliver)
        debug_printf("waitpid() returned -1/ECHILD: checking explicitly "
          "for process existence\n");

      for (poffset = 0; poffset < remote_max_parallel; poffset++)
        {
        if ((pid = parlist[poffset].pid) != 0 && kill(pid, 0) == 0)
          {
          DEBUG(D_deliver) debug_printf("process %d still exists: assume "
            "stolen by strace\n", (int)pid);
          break;
          }
        }

      if (poffset >= remote_max_parallel)
        {
        DEBUG(D_deliver) debug_printf("*** no delivery children found\n");
        return NULL;
        }
      }


    DEBUG(D_deliver) debug_printf("selecting on subprocess pipes\n");

    maxpipe = 0;
    FD_ZERO(&select_pipes);
    for (poffset = 0; poffset < remote_max_parallel; poffset++)
      if (parlist[poffset].pid != 0)
        {
        int fd = parlist[poffset].fd;
        FD_SET(fd, &select_pipes);
        if (fd > maxpipe) maxpipe = fd;
        }


    tv.tv_sec = 60;
    tv.tv_usec = 0;

    readycount = select(maxpipe + 1, (SELECT_ARG2_TYPE *)&select_pipes,
         NULL, NULL, &tv);


    for (poffset = 0;
         readycount > 0 && poffset < remote_max_parallel;
         poffset++)
      {
      if (  (pid = parlist[poffset].pid) != 0
         && FD_ISSET(parlist[poffset].fd, &select_pipes)
	 )
        {
        readycount--;
        if (par_read_pipe(poffset, FALSE))
          for (;;)
            {
            pid_t endedpid = waitpid(pid, &status, 0);
            if (endedpid == pid) goto PROCESS_DONE;
            if (endedpid != (pid_t)(-1) || errno != EINTR)
              log_write(0, LOG_MAIN|LOG_PANIC_DIE, "Unexpected error return "
                "%d (errno = %d) from waitpid() for process %d",
                (int)endedpid, errno, (int)pid);
            }
        }
      }


    }


  for (poffset = 0; poffset < remote_max_parallel; poffset++)
    if (pid == parlist[poffset].pid) break;


  if (poffset < remote_max_parallel) break;


  log_write(0, LOG_MAIN|LOG_PANIC, "Process %d finished: not found in remote "
    "transport process list", pid);
  }


PROCESS_DONE:

DEBUG(D_deliver)
  {
  if (status == 0)
    debug_printf("remote delivery process %d ended\n", (int)pid);
  else
    debug_printf("remote delivery process %d ended: status=%04x\n", (int)pid,
      status);
  }

set_process_info("delivering %s", message_id);


addrlist = parlist[poffset].addrlist;


if ((status & 0xffff) != 0)
  {
  uschar *msg;
  int msb = (status >> 8) & 255;
  int lsb = status & 255;
  int code = (msb == 0)? (lsb & 0x7f) : msb;

  msg = string_sprintf("%s transport process returned non-zero status 0x%04x: "
    "%s %d",
    addrlist->transport->driver_name,
    status,
    (msb == 0)? "terminated by signal" : "exit code",
    code);

  if (msb != 0 || (code != SIGTERM && code != SIGKILL && code != SIGQUIT))
    addrlist->special_action = SPECIAL_FREEZE;

  for (addr = addrlist; addr; addr = addr->next)
    {
    addr->transport_return = DEFER;
    addr->message = msg;
    }

  remove_journal = FALSE;
  }


else if (!parlist[poffset].done) (void)par_read_pipe(poffset, TRUE);


transport_count = parlist[poffset].transport_count;
used_return_path = parlist[poffset].return_path;
parlist[poffset].pid = 0;
parcount--;
return addrlist;
}
