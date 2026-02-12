usr1_handler(int sig)
{
int fd;

os_restarting_signal(sig, usr1_handler);

if ((fd = Uopen(process_log_path, O_APPEND|O_WRONLY, LOG_MODE)) < 0)
  {


  int euid = geteuid();
  if (euid == exim_uid)
    fd = Uopen(process_log_path, O_CREAT|O_APPEND|O_WRONLY, LOG_MODE);
  else if (euid == root_uid)
    fd = log_create_as_exim(process_log_path);
  }


if (fd < 0) return;

(void)write(fd, process_info, process_info_len);
(void)close(fd);
}
