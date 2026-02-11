read_command(void)
{
  struct command* cmd;

AGAIN:
  if (command_queue != NULL) {
    cmd = command_queue;
    command_queue = cmd->next;
    return cmd;
  }

  while (1) {

    char* p;
    for (p = conn->rbuf; p < conn->rbuf + conn->n_rbuf; p++) {
      if (*p == '\n') {
	*p = '\0';
	cmd = make_command(conn->rbuf);
	conn->n_rbuf -= p + 1 - conn->rbuf;
	memmove(conn->rbuf, p + 1, conn->n_rbuf);
	if (cmd) {
	  command_queue = cmd;
	  goto AGAIN;
	}
      }
    }

    if (proc_connection() == -1) {
      return NULL;
    }

  }
}
