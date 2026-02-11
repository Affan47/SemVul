ev_io_register(ev_loop_t* loop, int fd, EV_TYPE events, cb_io_t cb, void *ptr) {
    if (fd >= loop->maxevent) {
        return -1;
    }
	if (!(events & EV_READ || events & EV_WRITE)) {
		fprintf(stderr, "invalid events\n");
		return -1;
	}
	if (fd < 0) {
		fprintf(stderr, "invalid fd:%d\n", fd);
		return -1;
	}
	if (ptr != NULL) {
		loop->iomap[fd].ptr = ptr;
	}

	if ((loop->iomap[fd].events & events) == events) {
		if (loop->iomap[fd].events & EV_READ) {
			loop->iomap[fd].cb_read = cb;
		}
		if (loop->iomap[fd].events & EV_WRITE) {
			loop->iomap[fd].cb_write = cb;
		}
	}

	else {
		if (EV_READ & events) {
			loop->iomap[fd].cb_read = cb;
		}
		if (EV_WRITE & events) {
			loop->iomap[fd].cb_write = cb;
		}
		loop->iomap[fd].events |= events;

		struct epoll_event ev;
		ev.events = loop->iomap[fd].events;
		if (loop->etmodel) {
			ev.events |= EPOLLET;
		}
		ev.data.fd = fd;

		if(loop->iomap[fd].active) {
			if(-1 == epoll_ctl(loop->epfd, EPOLL_CTL_MOD, fd, &ev)) {
				fprintf(stderr, "ERROR: epoll_ctl mod in ev_register: %s\n", strerror(errno));
				ev_io_clear(loop, fd);
				return -1;
			}
		}
		else {
			if(-1 == epoll_ctl(loop->epfd, EPOLL_CTL_ADD, fd, &ev)) {
				fprintf(stderr, "ERROR: epoll_ctl add in ev_register: %s\n", strerror(errno));
				ev_io_unregister(loop, fd);
				return -1;
			}
		}
	}
	loop->iomap[fd].active = 1;
	return 0;
}
