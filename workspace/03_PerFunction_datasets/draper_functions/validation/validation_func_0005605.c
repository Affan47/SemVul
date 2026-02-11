log_from_pipe(FILE *stream, int severity, const char *executable,
              int *child_status)
{
  char buf[256];
  enum stream_status r;

  for (;;) {
    r = get_string_from_pipe(stream, buf, sizeof(buf) - 1);

    if (r == IO_STREAM_CLOSED) {
      return 1;
    } else if (r == IO_STREAM_EAGAIN) {
      return 0;
    } else if (r == IO_STREAM_TERM) {
      return -1;
    }

    tor_assert(r == IO_STREAM_OKAY);


    if (strcmpstart(buf, SPAWN_ERROR_MESSAGE) == 0) {

      int retval, child_state, saved_errno;
      retval = tor_sscanf(buf, SPAWN_ERROR_MESSAGE "%x/%x",
                          &child_state, &saved_errno);
      if (retval == 2) {
        log_warn(LD_GENERAL,
                 "Failed to start child process \"%s\" in state %d: %s",
                 executable, child_state, strerror(saved_errno));
        if (child_status)
          *child_status = 1;
      } else {


        log_warn(LD_GENERAL,
                 "Unexpected message from port forwarding helper \"%s\": %s",
                 executable, buf);
      }
    } else {
      log_fn(severity, LD_GENERAL, "Port forwarding helper says: %s", buf);
    }
  }


  return -1;
}
