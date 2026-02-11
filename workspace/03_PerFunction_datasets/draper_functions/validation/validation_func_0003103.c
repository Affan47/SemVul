handle_connection(const char *agiurl, const struct ast_sockaddr addr, const int netsockfd)
{
	struct pollfd pfds[1];
	int res, conresult;
	socklen_t reslen;

	reslen = sizeof(conresult);

	pfds[0].fd = netsockfd;
	pfds[0].events = POLLOUT;

	while ((res = ast_poll(pfds, 1, MAX_AGI_CONNECT)) != 1) {
		if (errno != EINTR) {
			if (!res) {
				ast_log(LOG_WARNING, "FastAGI connection to '%s' timed out after MAX_AGI_CONNECT (%d) milliseconds.\n",
					agiurl, MAX_AGI_CONNECT);
			} else {
				ast_log(LOG_WARNING, "Connect to '%s' failed: %s\n", agiurl, strerror(errno));
			}

			return 1;
		}
	}

	if (getsockopt(pfds[0].fd, SOL_SOCKET, SO_ERROR, &conresult, &reslen) < 0) {
		ast_log(LOG_WARNING, "Connection to %s failed with error: %s\n",
			ast_sockaddr_stringify(&addr), strerror(errno));
		return 1;
	}

	if (conresult) {
		ast_log(LOG_WARNING, "Connecting to '%s' failed for url '%s': %s\n",
			ast_sockaddr_stringify(&addr), agiurl, strerror(conresult));
		return 1;
	}

	return 0;
}
