accept_thread(void *arg)
{
    int fd;
    int new_fd;
    int port;
    socklen_t addrlen;
    struct sockaddr addr;
    long smsbox_thread_id;

    port = *(int *) arg;
    fd = make_server_socket(port, NULL);
    if (fd == -1)
    	panic(0, "Couldn't create SMPP listen port.");

    smsbox_thread_id = -1;
    for (;;) {
	if (gwthread_pollfd(fd, POLLIN, -1.0) != POLLIN)
	    break;
	addrlen = sizeof(addr);
	new_fd = accept(fd, &addr, &addrlen);
    	if (start_time == (time_t) -1)
	    time(&start_time);
	gwthread_create(receive_smpp_thread,
			esme_create(conn_wrap_fd(new_fd, 0)));
	if (smsbox_thread_id == -1)
	    smsbox_thread_id = gwthread_create(smsbox_thread, NULL);
    }

    debug("test.smpp", 0, "%s terminates.", __func__);
}
