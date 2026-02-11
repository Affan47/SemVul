create_and_bind_or_die(const char *bindaddr, int port, int sock_type)
{
	int fd;
	len_and_sockaddr *lsa;

	if (bindaddr && bindaddr[0]) {
		lsa = xdotted2sockaddr(bindaddr, port);

		fd = xsocket(lsa->u.sa.sa_family, sock_type, 0);
	} else {
		fd = xsocket_type(&lsa, AF_UNSPEC, sock_type);
		set_nport(&lsa->u.sa, htons(port));
	}
	setsockopt_reuseaddr(fd);
	xbind(fd, &lsa->u.sa, lsa->len);
	free(lsa);
	return fd;
}
