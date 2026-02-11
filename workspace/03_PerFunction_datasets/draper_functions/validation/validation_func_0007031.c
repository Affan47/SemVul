mread(int fd, char *buf, int4 nbytes)
{
	int		nread;
	int		r;

	nread = 0;

	do {
		r = read(fd, buf, nbytes);

		if (r < 0) {

			if (errno != EINTR) {
				return(ERROR);
			}
		} else if ((r == 0) && (nbytes > 0)) {
			errno = EEOF;
			return((int4) nread);
		} else {
			nread += r;
			buf += r;
			nbytes -= r;
		}
	} while (nbytes > 0);

	return((int4) nread);
}
