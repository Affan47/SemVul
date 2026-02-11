child_reaper(int sig)
{
	pid_t pid;

	while (( pid = waitpid(-1, NULL, 0)) > 0)
		jobdelete(pid);
	if (errno != ECHILD)
			;

	return;
}
