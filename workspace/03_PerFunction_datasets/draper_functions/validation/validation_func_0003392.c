exec_kernel_doc(char **svec)
{
	pid_t pid;
	int ret;
	char real_filename[PATH_MAX + 1];

	fflush(stdout);
	switch (pid=fork()) {
		case -1:
			perror("fork");
			exit(1);
		case  0:
			memset(real_filename, 0, sizeof(real_filename));
			strncat(real_filename, kernsrctree, PATH_MAX);
			strncat(real_filename, "/" KERNELDOCPATH KERNELDOC,
					PATH_MAX - strlen(real_filename));
			execvp(real_filename, svec);
			fprintf(stderr, "exec ");
			perror(real_filename);
			exit(1);
		default:
			waitpid(pid, &ret ,0);
	}
	if (WIFEXITED(ret))
		exitstatus |= WEXITSTATUS(ret);
	else
		exitstatus = 0xff;
}
