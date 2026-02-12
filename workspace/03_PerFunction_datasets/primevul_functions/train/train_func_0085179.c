report_fork_failure_to_client(Port *port, int errnum)
{
	char		buffer[1000];
	int			rc;


	snprintf(buffer, sizeof(buffer), "E%s%s\n",
			 _("could not fork new process for connection: "),
			 strerror(errnum));


	if (!pg_set_noblock(port->sock))
		return;


	do
	{
		rc = send(port->sock, buffer, strlen(buffer) + 1, 0);
	} while (rc < 0 && errno == EINTR);
}
