static int qh_input(int sd, int events, void *ioc_)
{
	iocache * ioc = (iocache *) ioc_;
	int result    = 0;


	if (sd == qh_listen_sock) {

		struct sockaddr sa;
		socklen_t slen = 0;
		int nsd        = 0;


		memset(&sa, 0, sizeof(sa));
		nsd = accept(sd, &sa, &slen);
		if (qh_max_running && qh_running >= qh_max_running) {
			nsock_printf(nsd, "503: Server full");
			close(nsd);
			return 0;
		}

		ioc = iocache_create(16384);
		if (ioc == NULL) {
			logit(NSLOG_RUNTIME_ERROR, TRUE, "qh: Failed to create iocache for inbound request\n");
			nsock_printf(nsd, "500: Internal server error");
			close(nsd);
			return 0;
		}


		result = iobroker_register(nagios_iobs, nsd, ioc, qh_input);
		if (result < 0) {
			logit(NSLOG_RUNTIME_ERROR, TRUE, "qh: Failed to register input socket %d with I/O broker: %s\n", nsd, strerror(errno));
			iocache_destroy(ioc);
			close(nsd);
			return 0;
		}


		worker_set_sockopts(nsd, 0);
		qh_running++;
		return 0;
	}


	else {

		unsigned long len         = 0;
		unsigned int query_len    = 0;
		struct query_handler * qh = NULL;
		char * buf                = NULL;
		char * space              = NULL;
		char * handler            = NULL;
		char * query              = NULL;

		result = iocache_read(ioc, sd);


		if (result == 0 || (result < 0 && errno == EPIPE)) {
			iocache_destroy(ioc);
			iobroker_close(nagios_iobs, sd);
			qh_running--;
			return 0;
		}


		buf = iocache_use_delim(ioc, "\0", 1, &len);
		if (buf == NULL) {
			return 0;
		}


		if (*buf == '@' || *buf == '#') {
			handler = buf + 1;
		}


		space = strchr(buf, ' ');
		if (space != NULL) {
			*space = 0;
			query = space + 1;
			query_len = len - (unsigned long)(query - buf);
		}


		qh = qh_find_handler(handler);


		if (qh == NULL) {
			nsock_printf(sd, "404: %s: No such handler", handler);
			iobroker_close(nagios_iobs, sd);
			iocache_destroy(ioc);
			return 0;
		}


		while (query_len > 0
		       && (query[query_len - 1] == 0 || query[query_len - 1] == '\n')) {

			query[--query_len] = 0;
		}


		result = qh->handler(sd, query, query_len);
		if (result >= 100) {
			nsock_printf_nul(sd, "%d: %s", result, qh_strerror(result));
		}


		if (result >= 300 || *buf == '#') {
			iobroker_close(nagios_iobs, sd);
			iocache_destroy(ioc);
			return 0;
		}


		switch (result) {


		case QH_CLOSE:


		case -1:
			iobroker_close(nagios_iobs, sd);


		case QH_TAKEOVER:


		case 101:
			iocache_destroy(ioc);
			break;
		}
	}

	return 0;
}
