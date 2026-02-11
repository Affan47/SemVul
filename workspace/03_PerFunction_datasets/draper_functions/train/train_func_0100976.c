check_dpkglock()
{
    int fd;
    struct flock fl;
    if (getuid()) {

	return 0;
    }
    fd = open_internal(DPKG_LOCKFILE, O_RDWR|O_CREAT|O_TRUNC, 0660);
    if (fd == -1)
	return 0;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 1;
    if (fcntl(fd, F_SETLK, &fl) == -1) {
	close(fd);
	if (errno == EWOULDBLOCK || errno == EAGAIN || errno == EACCES)
	    return 1;

	return 1;
    }
    fl.l_type = F_UNLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 1;
    if (fcntl(fd, F_SETLK, &fl) == -1) {

    }
    close(fd);
    return 0;
}
