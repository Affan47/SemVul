check_child_procs (void)
{
  rp_child_info *cur;
  int pid, status;
  while (1)
    {
      pid = waitpid (WAIT_ANY, &status, WNOHANG);
      if (pid <= 0)
        break;

      PRINT_DEBUG(("Child status: %d\n", WEXITSTATUS (status)));


      list_for_each_entry (cur, &rp_children, node)
        {
          if (cur->pid == pid)
            {
              cur->terminated = 1;
              cur->status = WEXITSTATUS (status);
              break;
            }
        }

      chld_signalled = 1;
    }
}
