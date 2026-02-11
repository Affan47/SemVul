netsys_create_event_aggreg(value cancelv)
{
#ifdef HAVE_POLL_AGGREG
    struct poll_aggreg *pa;
    value r;
    int fd, cancel_fd;
    int code;
    int e;

#ifdef USABLE_EPOLL
    fd = epoll_create(128);
    if (fd == -1) uerror("epoll_create", Nothing);
    code = fcntl(fd, F_SETFD, FD_CLOEXEC);
    if (code == -1) {
	e = errno;
	close(fd);
	unix_error(e, "fcntl", Nothing);
    };
    r = alloc_poll_aggreg();
    pa = *(Poll_aggreg_val(r));
    pa->fd = fd;
    pa->need_cancel = Bool_val(cancelv);
    pa->cancel_fd = -1;
    if (pa->need_cancel) {
	struct epoll_event ee;

	cancel_fd = eventfd(0, 0);
	if (cancel_fd == -1) {
	    e = errno;
	    close(fd);
	    unix_error(e, "eventfd", Nothing);
	};
	code = fcntl(cancel_fd, F_SETFD, FD_CLOEXEC);
	if (code == -1) {
	    e = errno;
	    close(fd);
	    close(cancel_fd);
	    unix_error(e, "fcntl", Nothing);
	};
	ee.events = EPOLLIN;
	ee.data.u64 = 1;
	code = epoll_ctl(fd, EPOLL_CTL_ADD, cancel_fd, &ee);
	if (code == -1) {
	    e = errno;
	    close(fd);
	    close(cancel_fd);
	    unix_error(e, "epoll_ctl (ADD)", Nothing);
	};
	pa->cancel_fd = cancel_fd;
    };
#endif
    return r;
#else
    invalid_argument("Netsys_posix.create_event_aggregator not available");
#endif
}
