log_create_as_exim(uschar *name)
{
pid_t pid = fork();
int status = 1;
int fd = -1;


if (pid == 0)
  {
  if (setgid(exim_gid) < 0)
    die(US"exim: setgid for log-file creation failed, aborting",
      US"Unexpected log failure, please try later");
  if (setuid(exim_uid) < 0)
    die(US"exim: setuid for log-file creation failed, aborting",
      US"Unexpected log failure, please try later");
  _exit((log_create(name) < 0)? 1 : 0);
  }


while (pid > 0 && waitpid(pid, &status, 0) != pid);
if (status == 0) fd = Uopen(name,
#ifdef O_CLOEXEC
			O_CLOEXEC |
#endif
		       	O_APPEND|O_WRONLY, LOG_MODE);


return fd;
}
