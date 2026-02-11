lam_port_is_open(int port)
{
	port -= LAM_PORTLOW;
	if (!((0 <= port) && (port < LAM_PORTMAX))) {
		errno = EINVAL;
		return(LAMERROR);
	}

	return(ports[port]);
}
