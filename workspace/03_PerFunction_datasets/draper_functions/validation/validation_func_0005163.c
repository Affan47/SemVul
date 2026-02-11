eliminatePipe(pid_t child)
{
	unsigned int seconds;


	DPRINTF("trying to wait for child (WNOHANG) (pid %d)", child);
	if (waitpid(child, NULL, WNOHANG) > 0) return;

	DPRINTF("sleep 2 seconds and try again to wait for pid %d", child);

	sleep(2);
	if (waitpid(child, NULL, WNOHANG) > 0) return;


	DPRINTF("killing (SIGTERM) child pid %d", child);
	kill(child, SIGTERM);


	for (seconds = 10; seconds > 0; sleep(1), seconds--)
		if (waitpid(child, NULL, WNOHANG) > 0) return;


	DPRINTF("killing (SIGKILL) child pid %d", child);
	if (kill(child, SIGKILL) == 0)
	{

		DPRINTF("waitpiding for child pid (blocking!) %d)", child);
		waitpid(child, NULL, 0);
	}
	else
	{

		DPRINTF("error when sending sigkill to %d", child);
		if (errno != ESRCH) return;


		DPRINTF("maybe because already dead (pid: %d)", child);
		waitpid(child, NULL, WNOHANG);
	}
}
