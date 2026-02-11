daemonize(void)
{
	pid_t pid;

	pid = fork();
	if (pid < 0)
		return FALSE;
	if (pid > 0)
		exit(0);

	if (setsid() < 0)
		return FALSE;

	pid = fork();
	if (pid < 0)
		return FALSE;
	if (pid > 0)
		exit(0);

	if (chdir("/") < 0)
		return FALSE;

	umask(0);

	if (freopen("/dev/null", "r", stdin) == NULL ||
	    freopen("/dev/null", "w", stdout) == NULL ||
	    freopen("/dev/null", "w", stderr) == NULL) {
		nhrp_error("Unable reopen standard file descriptors");
		goto err;
	}

	ev_default_fork();

	return TRUE;

err:
	close(pid_file_fd);
	pid_file_fd = 0;
	return FALSE;
}
