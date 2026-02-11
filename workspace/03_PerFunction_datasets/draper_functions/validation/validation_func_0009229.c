localsock_callback(int fd)
{
    int remote_fd;
    char buf[1024];

    remote_fd = get_fd_from_userpipe(buf, fd);
    if (remote_fd != -1)
    {
	cr.new_caller(remote_fd, -1, buf, socket_callback);
    }
    else
    {

	cr.lost_server();
    }
}
