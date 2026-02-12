transport_write_message(transport_ctx * tctx, int size_limit)
{
BOOL last_filter_was_NL = TRUE;
BOOL save_spool_file_wireformat = f.spool_file_wireformat;
int rc, len, yield, fd_read, fd_write, save_errno;
int pfd[2] = {-1, -1};
pid_t filter_pid, write_pid;

f.transport_filter_timed_out = FALSE;


if (  !transport_filter_argv
   || !*transport_filter_argv
   || !**transport_filter_argv
   )
  return internal_transport_write_message(tctx, size_limit);


nl_partial_match = -1;

if (tctx->check_string && tctx->escape_string)
  {
  nl_check = tctx->check_string;
  nl_check_length = Ustrlen(nl_check);
  nl_escape = tctx->escape_string;
  nl_escape_length = Ustrlen(nl_escape);
  }
else nl_check_length = nl_escape_length = 0;


fd_read = -1;
fd_write = -1;
save_errno = 0;
yield = FALSE;
write_pid = (pid_t)(-1);

  {
  int bits = fcntl(tctx->u.fd, F_GETFD);
  (void)fcntl(tctx->u.fd, F_SETFD, bits | FD_CLOEXEC);
  filter_pid = child_open(USS transport_filter_argv, NULL, 077,
   &fd_write, &fd_read, FALSE);
  (void)fcntl(tctx->u.fd, F_SETFD, bits & ~FD_CLOEXEC);
  }
if (filter_pid < 0) goto TIDY_UP;

DEBUG(D_transport)
  debug_printf("process %d running as transport filter: fd_write=%d fd_read=%d\n",
    (int)filter_pid, fd_write, fd_read);


if (pipe(pfd) != 0) goto TIDY_UP;
if ((write_pid = fork()) == 0)
  {
  BOOL rc;
  (void)close(fd_read);
  (void)close(pfd[pipe_read]);
  nl_check_length = nl_escape_length = 0;

  tctx->u.fd = fd_write;
  tctx->check_string = tctx->escape_string = NULL;
  tctx->options &= ~(topt_use_crlf | topt_end_dot | topt_use_bdat);

  rc = internal_transport_write_message(tctx, size_limit);

  save_errno = errno;
  if (  write(pfd[pipe_write], (void *)&rc, sizeof(BOOL))
        != sizeof(BOOL)
     || write(pfd[pipe_write], (void *)&save_errno, sizeof(int))
        != sizeof(int)
     || write(pfd[pipe_write], (void *)&tctx->addr->more_errno, sizeof(int))
        != sizeof(int)
     || write(pfd[pipe_write], (void *)&tctx->addr->delivery_usec, sizeof(int))
        != sizeof(int)
     )
    rc = FALSE;
  _exit(0);
  }
save_errno = errno;


(void)close(pfd[pipe_write]);
(void)close(fd_write);
fd_write = -1;


if (write_pid < 0)
  {
  errno = save_errno;
  goto TIDY_UP;
  }


if (f.running_in_test_harness) millisleep(250);

DEBUG(D_transport)
  debug_printf("process %d writing to transport filter\n", (int)write_pid);


DEBUG(D_transport) debug_printf("copying from the filter\n");


f.spool_file_wireformat = FALSE;
chunk_ptr = deliver_out_buffer;

for (;;)
  {
  sigalrm_seen = FALSE;
  ALARM(transport_filter_timeout);
  len = read(fd_read, deliver_in_buffer, DELIVER_IN_BUFFER_SIZE);
  ALARM_CLR(0);
  if (sigalrm_seen)
    {
    errno = ETIMEDOUT;
    f.transport_filter_timed_out = TRUE;
    goto TIDY_UP;
    }


  if (len > 0)
    {
    if (!write_chunk(tctx, deliver_in_buffer, len)) goto TIDY_UP;
    last_filter_was_NL = (deliver_in_buffer[len-1] == '\n');
    }


  else
    {
    if (len == 0) yield = TRUE;
    break;
    }
  }


TIDY_UP:
f.spool_file_wireformat = save_spool_file_wireformat;
save_errno = errno;

(void)close(fd_read);
if (fd_write > 0) (void)close(fd_write);

if (!yield)
  {
  if (filter_pid > 0) kill(filter_pid, SIGKILL);
  if (write_pid > 0)  kill(write_pid, SIGKILL);
  }


DEBUG(D_transport) debug_printf("waiting for filter process\n");
if (filter_pid > 0 && (rc = child_close(filter_pid, 30)) != 0 && yield)
  {
  yield = FALSE;
  save_errno = ERRNO_FILTER_FAIL;
  tctx->addr->more_errno = rc;
  DEBUG(D_transport) debug_printf("filter process returned %d\n", rc);
  }


DEBUG(D_transport) debug_printf("waiting for writing process\n");
if (write_pid > 0)
  {
  rc = child_close(write_pid, 30);
  if (yield)
    if (rc == 0)
      {
      BOOL ok;
      if (read(pfd[pipe_read], (void *)&ok, sizeof(BOOL)) != sizeof(BOOL))
	{
	DEBUG(D_transport)
	  debug_printf("pipe read from writing process: %s\n", strerror(errno));
	save_errno = ERRNO_FILTER_FAIL;
        yield = FALSE;
	}
      else if (!ok)
        {
	int dummy = read(pfd[pipe_read], (void *)&save_errno, sizeof(int));
        dummy = read(pfd[pipe_read], (void *)&tctx->addr->more_errno, sizeof(int));
        dummy = read(pfd[pipe_read], (void *)&tctx->addr->delivery_usec, sizeof(int));
	dummy = dummy;
        yield = FALSE;
        }
      }
    else
      {
      yield = FALSE;
      save_errno = ERRNO_FILTER_FAIL;
      tctx->addr->more_errno = rc;
      DEBUG(D_transport) debug_printf("writing process returned %d\n", rc);
      }
  }
(void)close(pfd[pipe_read]);


if (yield)
  {
  nl_check_length = nl_escape_length = 0;
  f.spool_file_wireformat = FALSE;
  if (  tctx->options & topt_end_dot
     && ( last_filter_was_NL
        ? !write_chunk(tctx, US".\n", 2)
	: !write_chunk(tctx, US"\n.\n", 3)
     )  )
    yield = FALSE;


  else
    yield = (len = chunk_ptr - deliver_out_buffer) <= 0
	  || transport_write_block(tctx, deliver_out_buffer, len, FALSE);
  }
else
  errno = save_errno;

DEBUG(D_transport)
  {
  debug_printf("end of filtering transport writing: yield=%d\n", yield);
  if (!yield)
    debug_printf("errno=%d more_errno=%d\n", errno, tctx->addr->more_errno);
  }

return yield;
}
