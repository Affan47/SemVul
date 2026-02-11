connect_egd(const char *path)
{
    struct sockaddr_un addr;
    int fd;

    memset(&addr, 0, sizeof(addr));

    if (strlen(path) > sizeof(addr.sun_path))
	return -1;

    addr.sun_family = AF_UNIX;
    strlcpy(addr.sun_path, path, sizeof(addr.sun_path));

    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0)
	return -1;

    rk_cloexec(fd);

    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) != 0) {
	close(fd);
	return -1;
    }

    return fd;
}
