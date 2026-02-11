get_random_bytes(const int count)
{
    char *buf;
    int fd;

    buf = NOFAIL(malloc(count));
    fd = open(RANDOM_DEVICE, O_RDONLY);
    if (fd < 0) {
	perror("open(" RANDOM_DEVICE ")");
	exit(2);
    }
    if (read(fd, buf, count) != count) {
	if (count < 0)
	    perror("read(" RANDOM_DEVICE ")");
	else
	    fprintf(stderr, "Short read of %s.\n", RANDOM_DEVICE);
	exit(2);
    }
    close(fd);

    return buf;
}
