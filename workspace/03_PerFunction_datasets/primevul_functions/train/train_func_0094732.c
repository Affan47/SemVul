int radius_event_init(CONF_SECTION *cs, int spawn_flag)
{
	rad_listen_t *this, *head = NULL;

	if (el) return 0;

	time(&fr_start_time);

	el = fr_event_list_create(event_status);
	if (!el) return 0;

	pl = fr_packet_list_create(0);
	if (!pl) return 0;

	request_num_counter = 0;

#ifdef WITH_PROXY
	if (mainconfig.proxy_requests) {


		proxy_list = fr_packet_list_create(1);
		if (!proxy_list) return 0;

#ifdef HAVE_PTHREAD_H
		if (pthread_mutex_init(&proxy_mutex, NULL) != 0) {
			radlog(L_ERR, "FATAL: Failed to initialize proxy mutex: %s",
			       strerror(errno));
			exit(1);
		}
#endif
	}
#endif

#ifdef HAVE_PTHREAD_H
#ifndef __MINGW32__
	NO_SUCH_CHILD_PID = (pthread_t ) (0);
#else
	NO_SUCH_CHILD_PID = pthread_self();
#endif


	if (spawn_flag && !check_config &&
	    (thread_pool_init(cs, &spawn_flag) < 0)) {
		exit(1);
	}
#endif


	have_children = spawn_flag;

	if (check_config) {
		DEBUG("%s: #### Skipping IP addresses and Ports ####",
		       mainconfig.name);
		return 1;
	}

#ifdef WITH_SELF_PIPE


	if (pipe(self_pipe) < 0) {
		radlog(L_ERR, "radiusd: Error opening internal pipe: %s",
		       strerror(errno));
		exit(1);
	}
	if (fcntl(self_pipe[0], F_SETFL, O_NONBLOCK | FD_CLOEXEC) < 0) {
		radlog(L_ERR, "radiusd: Error setting internal flags: %s",
		       strerror(errno));
		exit(1);
	}
	if (fcntl(self_pipe[1], F_SETFL, O_NONBLOCK | FD_CLOEXEC) < 0) {
		radlog(L_ERR, "radiusd: Error setting internal flags: %s",
		       strerror(errno));
		exit(1);
	}

	if (!fr_event_fd_insert(el, 0, self_pipe[0],
				  event_signal_handler, el)) {
		radlog(L_ERR, "Failed creating handler for signals");
		exit(1);
	}
#endif

#ifdef WITH_PROXY


	{
		int i;

		for (i = 0; i < 32; i++) proxy_fds[i] = -1;
	}
#endif

       DEBUG("%s: #### Opening IP addresses and Ports ####",
	       mainconfig.name);


	if (listen_init(cs, &head) < 0) {
		_exit(1);
	}


	fr_suid_down_permanent();


	for (this = head;
	     this != NULL;
	     this = this->next) {
		char buffer[256];

		this->print(this, buffer, sizeof(buffer));

		switch (this->type) {
#ifdef WITH_DETAIL
		case RAD_LISTEN_DETAIL:
			DEBUG("Listening on %s", buffer);


			this->status = RAD_LISTEN_STATUS_KNOWN;


			event_poll_detail(this);
			break;
#endif

#ifdef WITH_PROXY
		case RAD_LISTEN_PROXY:
			rad_assert(proxy_fds[this->fd & 0x1f] == -1);
			rad_assert(proxy_listeners[this->fd & 0x1f] == NULL);

			proxy_fds[this->fd & 0x1f] = this->fd;
			proxy_listeners[this->fd & 0x1f] = this;
			if (!fr_packet_list_socket_add(proxy_list,
							 this->fd)) {
				rad_assert(0 == 1);
			}

#endif

		default:
			break;
		}

		event_new_fd(this);
	}

	mainconfig.listen = head;

	return 1;
}
