get_header(int fd)
{
    static char	buffer[16384 + 3];
    char	*c, *p;
    long	n;

    n = sizeof(buffer);
    c = buffer;

    do {
	long	i = read(fd, c, 1024);

	if (i <= 0) {
	    if (i < 0)
		perror("read");
	    return NULL;
	}

	c[i] = '\0';
	c += i;
	n -= i;

	if ( (p = find_lflf(buffer)) ) {
	    *p = '\0';
	    return buffer;
	}
    } while (n > 0);

    return NULL;
}
