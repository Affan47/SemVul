pq_check_connection(void)
{
#if defined(POLLRDHUP)


	struct pollfd pollfd;
	int			rc;

	pollfd.fd = MyProcPort->sock;
	pollfd.events = POLLOUT | POLLIN | POLLRDHUP;
	pollfd.revents = 0;

	rc = poll(&pollfd, 1, 0);

	if (rc < 0)
	{
		ereport(COMMERROR,
				(errcode_for_socket_access(),
				 errmsg("could not poll socket: %m")));
		return false;
	}
	else if (rc == 1 && (pollfd.revents & (POLLHUP | POLLRDHUP)))
		return false;
#endif

	return true;
}
