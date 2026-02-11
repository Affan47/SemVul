checkscript(void)
{
	char *prog[2];
	struct stat s;
	int pid, w;

	if (stat("check", &s) == -1) {
		if (errno == ENOENT) return 1;
		bb_perror_msg(WARN"can't stat %s/check", *service);
		return 0;
	}

	prog[0] = (char*)"./check";
	prog[1] = NULL;
	pid = spawn(prog);
	if (pid <= 0) {
		bb_perror_msg(WARN"can't %s child %s/check", "run", *service);
		return 0;
	}
	while (safe_waitpid(pid, &w, 0) == -1) {
		bb_perror_msg(WARN"can't %s child %s/check", "wait for", *service);
		return 0;
	}
	return WEXITSTATUS(w) == 0;
}
