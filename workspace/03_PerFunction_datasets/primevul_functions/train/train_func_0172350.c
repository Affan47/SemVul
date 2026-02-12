static int talk_radius(radius_conf_t *conf, AUTH_HDR *request, AUTH_HDR *response,
		       char *password, char *old_password, int tries)
{
	socklen_t salen;
	int total_length;
	fd_set set;
	struct timeval tv;
	time_t now, end;
	int rcode;
	struct sockaddr saremote;
	struct sockaddr_in *s_in = (struct sockaddr_in *) &saremote;
	radius_server_t *server = conf->server;
	int ok;
	int server_tries;
	int retval;


	while (server != NULL) {

		memset(response, 0, sizeof(AUTH_HDR));


		if ((retval = host2server(server)) != PAM_SUCCESS) {
			_pam_log(LOG_ERR,
				 "Failed looking up IP address for RADIUS server %s (errcode=%d)",
				 server->hostname, retval);
			ok = FALSE;
			goto next;
		}


		memset ((char *) s_in, '\0', sizeof(struct sockaddr));
		s_in->sin_family = AF_INET;
		s_in->sin_addr.s_addr = htonl(server->ip.s_addr);
		s_in->sin_port = server->port;
		total_length = ntohs(request->length);

		if (!password) {
			get_accounting_vector(request, server);
		}

		server_tries = tries;
	send:

		if (sendto(conf->sockfd, (char *) request, total_length, 0,
			   &saremote, sizeof(struct sockaddr_in)) < 0) {
			_pam_log(LOG_ERR, "Error sending RADIUS packet to server %s: %s",
				 server->hostname, strerror(errno));
			ok = FALSE;
			goto next;
		}


		salen = sizeof(struct sockaddr);
		tv.tv_sec = server->timeout;
		tv.tv_usec = 0;
		FD_ZERO(&set);
		FD_SET(conf->sockfd, &set);

		time(&now);
		end = now + tv.tv_sec;


		ok = TRUE;
		while (ok) {
			rcode = select(conf->sockfd + 1, &set, NULL, NULL, &tv);


			if (rcode == 0) {
				_pam_log(LOG_ERR, "RADIUS server %s failed to respond", server->hostname);
				if (--server_tries) {
					goto send;
				}
				ok = FALSE;
				break;
			} else if (rcode < 0) {


				if (errno == EINTR) {
					time(&now);

					if (now > end) {
						_pam_log(LOG_ERR, "RADIUS server %s failed to respond",
							 server->hostname);
						if (--server_tries) goto send;
						ok = FALSE;
						break;
					}

					tv.tv_sec = end - now;
					if (tv.tv_sec == 0) {
						tv.tv_sec = 1;
					}

				} else {
					_pam_log(LOG_ERR, "Error waiting for response from RADIUS server %s: %s",
						 server->hostname, strerror(errno));
					ok = FALSE;
					break;
				}


			} else if (FD_ISSET(conf->sockfd, &set)) {


				if ((total_length = recvfrom(conf->sockfd, (void *) response, BUFFER_SIZE,
						     	     0, &saremote, &salen)) < 0) {
					_pam_log(LOG_ERR, "error reading RADIUS packet from server %s: %s",
					 	 server->hostname, strerror(errno));
					ok = FALSE;
					break;


				} else {
					char *p = server->secret;

					if ((ntohs(response->length) != total_length) ||
					    (ntohs(response->length) > BUFFER_SIZE)) {
						_pam_log(LOG_ERR, "RADIUS packet from server %s is corrupted",
						 	 server->hostname);
						ok = FALSE;
						break;
					}


					if (password) {
						if (old_password) {
#ifdef LIVINGSTON_PASSWORD_VERIFY_BUG_FIXED
							p = old_password;
#else
							p = "";
#endif
						}


					} else {
						if (conf->accounting_bug) {
							p = "";
						}
					}

					if (!verify_packet(p, response, request)) {
						_pam_log(LOG_ERR, "packet from RADIUS server %s failed verification: "
							 "The shared secret is probably incorrect.", server->hostname);
						ok = FALSE;
						break;
					}


					if (response->id != request->id) {
						_pam_log(LOG_WARNING, "Response packet ID %d does not match the "
							 "request packet ID %d: verification of packet fails",
							 response->id, request->id);
						ok = FALSE;
						break;
					}
				}


				break;
			}

		}


		next:
		if (!ok) {
			radius_server_t *old;

			old = server;
			server = server->next;
			conf->server = server;

			_pam_forget(old->secret);
			free(old->hostname);
			free(old);

			if (server) {

				get_random_vector(request->vector);
				request->id = request->vector[0];


				if (password) {
					get_random_vector(request->vector);
					if (old_password) {
						add_password(request, PW_PASSWORD, password, old_password);
						add_password(request, PW_OLD_PASSWORD, old_password, old_password);
					} else {
						add_password(request, PW_PASSWORD, password, server->secret);
					}
				}
			}
			continue;

		} else {

			cleanup(server->next);
			server->next = NULL;
			live_server = server;
			break;
		}
	}

	if (!server) {
		_pam_log(LOG_ERR, "All RADIUS servers failed to respond.");
		if (conf->localifdown)
			retval = PAM_IGNORE;
		else
			retval = PAM_AUTHINFO_UNAVAIL;
	} else {
		retval = PAM_SUCCESS;
	}

	return retval;
}
