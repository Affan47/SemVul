open_transformer(int fd,
	IF_DESKTOP(long long) int FAST_FUNC (*transformer)(int src_fd, int dst_fd),
	const char *transform_prog)
{
	struct fd_pair fd_pipe;
	int pid;

	xpiped_pair(fd_pipe);
	pid = BB_MMU ? xfork() : xvfork();
	if (pid == 0) {

		close(fd_pipe.rd);

#if BB_MMU
		transformer(fd, fd_pipe.wr);
		if (ENABLE_FEATURE_CLEAN_UP) {
			close(fd_pipe.wr);
			close(fd);
		}

		_exit(EXIT_SUCCESS);
#else
		{
			char *argv[4];
			xmove_fd(fd, 0);
			xmove_fd(fd_pipe.wr, 1);
			argv[0] = (char*)transform_prog;
			argv[1] = (char*)"-cf";
			argv[2] = (char*)"-";
			argv[3] = NULL;
			BB_EXECVP(transform_prog, argv);
			bb_perror_msg_and_die("can't execute '%s'", transform_prog);
		}
#endif

	}


	close(fd_pipe.wr);
	xmove_fd(fd_pipe.rd, fd);
}
