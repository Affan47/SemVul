fork_nicely(void *data, ChildCallback proc, int use_stderr)
{
    CHILD_CONTEXT	*context;
    pid_t		pid;
    int			stderr_fd[2];

    if (!use_stderr || pipe(stderr_fd) < 0) {
	stderr_fd[0] = -1;
	stderr_fd[1] = -1;
    }

    block_sigchld();
    pid = fork();

    if (pid == 0) {
	unblock_sigchld(False);
	setsid();

	if (!freopen("/dev/null", "w", stdout))
	    perror("/dev/null");
	if (stderr_fd[0] >= 0)
	    close(stderr_fd[0]);

	if (stderr_fd[1] >= 0 && stderr_fd[1] != STDERR_FILENO)
	    if (dup2(stderr_fd[1], STDERR_FILENO) < 0)
		perror("knews: dup2");

	unblock_sigpipe();

	return 0;
    }


    if (stderr_fd[1] >= 0)
	close(stderr_fd[1]);

    if (pid < 0) {
	perror("knews: fork");
	if (stderr_fd[0] >= 0)
	    close(stderr_fd[0]);
	unblock_sigchld(True);
	return -1;
    }

    context = create_child_context(pid, data, proc);
    if (stderr_fd[0] >= 0) {
	long	flags;

	if (fcntl(stderr_fd[0], F_SETFD, FD_CLOEXEC) < 0)
	    perror("fcntl");
	if ((flags = fcntl(stderr_fd[0], F_GETFL)) < 0 ||
	    fcntl(stderr_fd[0], F_SETFL, flags | O_NONBLOCK) < 0) {
	    perror("knews: fcntl");
	    close(stderr_fd[0]);
	    stderr_fd[0] = -1;
	} else {
	    context->stderr_buf = XtMalloc(STDERR_BUFFLEN);
	    context->stderr_buf[0] = '\0';
	    context->stderr_fd = stderr_fd[0];
	    context->stderr_id =
		XtAppAddInput(app_cont, stderr_fd[0],
			      (XtPointer)XtInputReadMask,
			      stderr_read_callback, (XtPointer)context);
	}
    }

    unblock_sigchld(True);

    return pid;
}
