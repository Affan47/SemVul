is_pipe(int fd)
{
	struct stat st;
	int pipe_mode=0;

	if (fstat(fd, &st) == 0) {
		if (S_ISFIFO(st.st_mode))
			pipe_mode = 1;
	}
	return pipe_mode;
}
