bqinput(const char *sep, int fd) {
	long n;
	char in[BUFSIZE];
	startsplit(sep, TRUE);

restart:
	while ((n = eread(fd, in, sizeof in)) > 0)
		splitstring(in, n, FALSE);
	SIGCHK();
	if (n == -1) {
		if (errno == EINTR)
			goto restart;
		close(fd);
		fail("$&backquote", "backquote read: %s", esstrerror(errno));
	}
	return endsplit();
}
