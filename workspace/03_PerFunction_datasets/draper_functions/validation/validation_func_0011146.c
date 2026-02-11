ev_stop(ev_loop_t *loop, int fd, EV_TYPE events) {

	if ( (fd_records[fd].events & events)) {
		if ((fd_records[fd].events & EV_READ) && (events & EV_READ)) {
			fd_records[fd].events &= (~EV_READ);
		}
		if ((fd_records[fd].events & EV_WRITE) && (events & EV_WRITE)) {
			fd_records[fd].events &= (~EV_WRITE);
		}

		struct epoll_event ev;
		ev.events = fd_records[fd].events;
		if (loop->etmodel) {
			ev.events |= EPOLLET;
		}
		ev.data.fd = fd;

		if (-1 == epoll_ctl(loop->epfd, EPOLL_CTL_MOD, fd, &ev)) {
			fprintf(stderr, "epoll_ctl mod in ev_stop\n");
			ev_clear(fd);
			return -1;
		}


		return 0;
	}
	return 0;
}
