sigchld_signal_handler
   ___P((int sig),
        (sig)
int sig;)
{
#ifdef USE_signal
  ___set_signal_handler (SIGCHLD, sigchld_signal_handler);
#endif


  for (;;)
    {
      int status;
      ___device *head;
      pid_t pid = waitpid_no_EINTR (-1, &status, WNOHANG);

      if (pid <= 0)
        break;


      head = ___global_device_group ()->list;

      if (head != NULL)
        {
          ___device *d = head->prev;

          do
            {
              if (___device_kind (d) == ___PROCESS_DEVICE_KIND)
                {
                  ___device_process *dev = ___CAST(___device_process*,d);

                  if (dev->pid == pid)
                    {
                      if (WIFEXITED(status) || WIFSIGNALED(status))
                        ___device_process_status_set (dev, status);
                      break;
                    }
                }
              d = d->prev;
            } while  (d != head);
        }
    }
}
