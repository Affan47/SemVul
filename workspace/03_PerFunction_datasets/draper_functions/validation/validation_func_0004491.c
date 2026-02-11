daemonize(void)
{
	pid_t pid;


	if ((pid = fork()) < 0)
		return false;
	if (pid != 0)
		exit(0);


	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);


	if (open("/dev/null", O_WRONLY) != 0)
		return false;
	if (dup2(0, STDERR_FILENO) != STDERR_FILENO)
		return false;
	close(0);


	setsid();

	if (chdir("/") != 0)
		return false;


	umask(0);
	return true;
}
