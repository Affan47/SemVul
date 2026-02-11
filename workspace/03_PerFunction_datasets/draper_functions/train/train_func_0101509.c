sockets_accept(int socket, void *buf, int len, sockets *ss)
{
	int new_sock, sas, ni;
	struct sockaddr_in sa;
	sas = sizeof(sa);
	new_sock = accept(ss->sock, (struct sockaddr *) &sa, (socklen_t *) &sas);
	if (new_sock < 0)
	{
		if (errno != EINTR)
		{
			LOG("sockets_accept: accept()");
			return 1;
		}
	}
	ni = sockets_add(new_sock, &sa, -1, TYPE_TCP, NULL, NULL, NULL);
	if (ss->action != NULL)
	{
		ss->action(s[ni]);
	}
	set_linux_socket_timeout(new_sock);

	return 1;
}
