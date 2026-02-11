dcc_connect_sok (struct DCC *dcc)
{
	int sok;
	struct sockaddr_in addr;

	sok = socket (AF_INET, SOCK_STREAM, 0);
	if (sok == -1)
		return -1;

	memset (&addr, 0, sizeof (addr));
	addr.sin_family = AF_INET;
	if (DCC_USE_PROXY ())
	{
		if (!dcc_lookup_proxy (prefs.hex_net_proxy_host, &addr))
		{
			closesocket (sok);
			return -1;
		}
		addr.sin_port = htons (prefs.hex_net_proxy_port);
	}
	else
	{
		addr.sin_port = htons (dcc->port);
		addr.sin_addr.s_addr = htonl (dcc->addr);
	}

	set_nonblocking (sok);
	connect (sok, (struct sockaddr *) &addr, sizeof (addr));

	return sok;
}
