touchDir(const char *dir) {
	pid_t pid;
	int e, status;

	pid = fork();
	if (pid == 0) {
		close(terminationPipe[0]);
		close(terminationPipe[1]);
		if (chdir(dir) == -1) {
			e = errno;
			fprintf(stderr, ERROR_PREFIX
				": cannot change working directory to %s: %s (errno %d)\n",
				dir, strerror(e), e);
			_exit(1);
		}
		execlp("/bin/sh", "/bin/sh", "-c",
			"find \"$1\" | xargs touch", "/bin/sh", ".",
			(const char * const) 0);
		e = errno;
		fprintf(stderr, ERROR_PREFIX ": cannot execute /bin/sh: %s (errno %d)\n",
			strerror(e), e);
		_exit(1);
	} else if (pid == -1) {
		e = errno;
		fprintf(stderr, ERROR_PREFIX ": cannot fork: %s (errno %d)\n",
			strerror(e), e);
		exit(1);
	} else {
		if (waitpid(pid, &status, 0) == -1) {
			if (errno != ESRCH && errno != EPERM) {
				fprintf(stderr, ERROR_PREFIX
					": unable to wait for shell command 'find %s | xargs touch'\n",
					dir);
				exit(1);
			}
		} else if (WEXITSTATUS(status) != 0) {
			fprintf(stderr, ERROR_PREFIX
				": shell command 'find %s | xargs touch' failed with exit status %d\n",
				dir, WEXITSTATUS(status));
			exit(1);
		}
	}
}
