get_random_fd(void)
{
	struct timeval	tv;
	static int	fd = -2;
	int		i;

	if (fd == -2) {
		gettimeofday(&tv, 0);
#ifndef _WIN32
		fd = open("/dev/urandom", O_RDONLY);
		if (fd == -1)
			fd = open("/dev/random", O_RDONLY | O_NONBLOCK);
		if (fd >= 0) {
			i = fcntl(fd, F_GETFD);
			if (i >= 0)
				fcntl(fd, F_SETFD, i | FD_CLOEXEC);
		}
#endif
		srand((getpid() << 16) ^ getuid() ^ tv.tv_sec ^ tv.tv_usec);
#ifdef DO_JRAND_MIX
		jrand_seed[0] = getpid() ^ (tv.tv_sec & 0xFFFF);
		jrand_seed[1] = getppid() ^ (tv.tv_usec & 0xFFFF);
		jrand_seed[2] = (tv.tv_sec ^ tv.tv_usec) >> 16;
#endif
	}

	gettimeofday(&tv, 0);
	for (i = (tv.tv_sec ^ tv.tv_usec) & 0x1F; i > 0; i--)
		rand();
	return fd;
}
