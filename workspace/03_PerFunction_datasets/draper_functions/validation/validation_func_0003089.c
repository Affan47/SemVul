resolve_host(struct inet_address *ip, const char *name, uint16_t port)
{
	IPaddress a;
	int r;

	r = SDLNet_ResolveHost(&a, name, port);
	if (!r)
	{
		ip->host = a.host;
		ip->port = a.port;
	}
	else
	{
		MSG("Couldn't resolve host '%s' port %u: %s\n", name, port, SDLNet_GetError());
	}

	return !r;
}
