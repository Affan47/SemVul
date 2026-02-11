jack_wake_next_client (jack_client_t* client)
{
#ifndef JACK_USE_MACH_THREADS
	struct pollfd pfds[1];
	int pret = 0;
	char c = 0;

	if (write (client->graph_next_fd, &c, sizeof (c))
	    != sizeof (c)) {
		DEBUG("cannot write byte to fd %d", client->graph_next_fd);
		jack_error ("cannot continue execution of the "
			    "processing graph (%s)",
			    strerror(errno));
		return -1;
	}

	DEBUG ("client sent message to next stage by %" PRIu64 "",
	       jack_get_microseconds());

	DEBUG("reading cleanup byte from pipe %d\n", client->graph_wait_fd);


	if (client->graph_wait_fd >= 0) {
		pfds[0].fd = client->graph_wait_fd;
		pfds[0].events = POLLIN;


		pret = poll(pfds, 1, 0);
	}

	if (pret > 0 && (pfds[0].revents & POLLIN)) {
		if (read (client->graph_wait_fd, &c, sizeof (c))
		    != sizeof (c)) {
			jack_error ("cannot complete execution of the "
				"processing graph (%s)", strerror(errno));
			return -1;
		}
	} else {
		DEBUG("cleanup byte from pipe %d not available?\n",
			client->graph_wait_fd);
	}
#endif
	return 0;
}
