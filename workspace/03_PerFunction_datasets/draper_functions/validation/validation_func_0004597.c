network_set_reuseaddr(socket_type fd)
{
    int flag = 1;
    const void *flagaddr = &flag;

    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, flagaddr, sizeof(flag)) < 0)
        syswarn("cannot mark bind address reusable");
}
