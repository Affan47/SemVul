ev_register(ev_loop_t*loop, int fd, EV_TYPE events, cb_func_t cb) {
	if (!(events & EV_READ || events & EV_WRITE)) {
		fprintf(stderr, "invalid events\n");
		return -1;
	}
	if (fd < 0) {
		fprintf(stderr, "invalid fd\n");
		return -1;
	}


	if ((fd_records[fd].events & events) == events) {

		if (fd_records[fd].events & EV_READ) {
			fd_records[fd].cb_read = cb;
		}
		if (fd_records[fd].events & EV_WRITE) {

			fd_records[fd].cb_write = cb;
		}
	}
	else {
		if (EV_READ & events) {
			fd_records[fd].cb_read = cb;
		}
		if (EV_WRITE & events) {
			fd_records[fd].cb_write = cb;
		}
		fd_records[fd].events |= events;

		struct epoll_event ev;
		ev.events = fd_records[fd].events;
		if (loop->etmodel) {
			ev.events |= EPOLLET;
		}
		ev.data.fd = fd;
		if (events == EV_WRITE) {
			if (-1 == epoll_ctl(loop->epfd, EPOLL_CTL_MOD, fd, &ev)) {
				fprintf(stderr, "epoll_ctl mod in ev_register: %s, fd:%d, %ld\n", strerror(errno), fd, gettid());
				ev_clear(fd);
				close(fd);
				return -1;
			}
		}
		else if (events == EV_READ) {
			if (-1 == epoll_ctl(loop->epfd, EPOLL_CTL_ADD, fd, &ev)) {
				fprintf(stderr, "epoll_ctl add in ev_register: %s, fd:%d, %ld\n", strerror(errno), fd, gettid());
				ev_unregister(loop, fd);
				close(fd);
				return -1;
			}
		}
		else {
			fprintf(stderr, "epoll_ctl undefined events\n");
			close(fd);
			return -1;
		}

	}
	fd_records[fd].active = 1;
	return 0;
}
