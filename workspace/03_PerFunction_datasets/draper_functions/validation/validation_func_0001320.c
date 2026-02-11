ev_create_loop(int maxevent, int et) {
	ev_loop_t *loop;
	loop = (ev_loop_t*)malloc(sizeof(ev_loop_t));
	loop->maxevent = maxevent;
	loop->etmodel = et;
	loop->epfd = epoll_create1(0);
	if (loop->epfd == -1) {
		return NULL;
	}
	loop->events = (struct epoll_event *)malloc(maxevent * sizeof(struct epoll_event));


	LOCK(lock_);
	if (fd_records == NULL) {
		fd_records = (fd_record_t *)malloc(maxevent * sizeof(fd_record_t));
		int i;
		for (i = 0; i < maxevent; i++) {
			fd_records[i].active = 0;
			fd_records[i].events = 0;
			fd_records[i].cb_read = NULL;
			fd_records[i].cb_write = NULL;

			fd_records[i].ffd = NO_FILE_FD;
			fd_records[i].write_pos = 0;
			fd_records[i].read_pos = 0;
			fd_records[i].total_len = 0;
			memset(fd_records[i].buf, 0, MAXBUFSIZE);
			memset(fd_records[i].path, 0, sizeof(fd_records[i].path));
			fd_records[i].http_code = 200;
			fd_records[i].keep_alive = 0;
			fd_records[i].timer_ptr = NULL;
		}
		printf("init\n");
	}

	UNLOCK(lock_);

	return loop;
}
