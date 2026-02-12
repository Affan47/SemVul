open_log(int *fd, int type, uschar *tag)
{
uid_t euid;
BOOL ok, ok2;
uschar buffer[LOG_NAME_SIZE];


ok = string_format(buffer, sizeof(buffer), CS file_path, log_names[type]);


if (type == lt_main && string_datestamp_offset >= 0)
  {
  Ustrcpy(mainlog_name, buffer);
  mainlog_datestamp = mainlog_name + string_datestamp_offset;
  }


else if (type == lt_reject && string_datestamp_offset >= 0)
  {
  Ustrcpy(rejectlog_name, buffer);
  rejectlog_datestamp = rejectlog_name + string_datestamp_offset;
  }


else if (type == lt_debug)
  {
  Ustrcpy(debuglog_name, buffer);
  if (tag)
    {

    ok2 = string_format(buffer, sizeof(buffer), "%s%s",
      debuglog_name, tag);
    if (ok2)
      Ustrcpy(debuglog_name, buffer);
    }
  }


else if (string_datestamp_offset >= 0)
  {
  uschar * from = buffer + string_datestamp_offset;
  uschar * to = from + string_datestamp_length;

  if (from == buffer || from[-1] == '/')
    {
    if (!isalnum(*to)) to++;
    }
  else
    if (!isalnum(from[-1])) from--;


  memmove(from, to, Ustrlen(to)+1);
  }


if (!ok)
  die(US"exim: log file path too long: aborting",
      US"Logging failure; please try later");


*fd = Uopen(buffer,
#ifdef O_CLOEXEC
		O_CLOEXEC |
#endif
	       	O_APPEND|O_WRONLY, LOG_MODE);

if (*fd >= 0)
  {
#ifndef O_CLOEXEC
  (void)fcntl(*fd, F_SETFD, fcntl(*fd, F_GETFD) | FD_CLOEXEC);
#endif
  return;
  }


euid = geteuid();


if (euid == exim_uid) *fd = log_create(buffer);


else if (euid == root_uid) *fd = log_create_as_exim(buffer);


if (*fd >= 0)
  {
#ifndef O_CLOEXEC
  (void)fcntl(*fd, F_SETFD, fcntl(*fd, F_GETFD) | FD_CLOEXEC);
#endif
  return;
  }


if (euid != root_uid && euid != exim_uid && log_stderr != NULL)
  {
  *fd = fileno(log_stderr);
  return;
  }


if (!panic_save_buffer)
  if ((panic_save_buffer = US malloc(LOG_BUFFER_SIZE)))
    memcpy(panic_save_buffer, log_buffer, LOG_BUFFER_SIZE);

log_write(0, LOG_PANIC_DIE, "Cannot open %s log file \"%s\": %s: "
  "euid=%d egid=%d", log_names[type], buffer, strerror(errno), euid, getegid());

}
