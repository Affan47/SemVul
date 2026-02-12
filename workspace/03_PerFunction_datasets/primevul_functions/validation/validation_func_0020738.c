detach(void)
{
#if defined(HAVE_DAEMON) && !defined(DEPRECATED_DAEMON)

	if(daemon(1, 0) != 0)
		fatal_exit("daemon failed: %s", strerror(errno));
#else
#ifdef HAVE_FORK
	int fd;

	switch (fork()) {
		case 0:
			break;
		case -1:
			fatal_exit("fork failed: %s", strerror(errno));
		default:

			exit(0);
	}

#ifdef HAVE_SETSID
	if(setsid() == -1)
		fatal_exit("setsid() failed: %s", strerror(errno));
#endif
	if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
		(void)dup2(fd, STDIN_FILENO);
		(void)dup2(fd, STDOUT_FILENO);
		(void)dup2(fd, STDERR_FILENO);
		if (fd > 2)
			(void)close(fd);
	}
#endif
#endif
}
