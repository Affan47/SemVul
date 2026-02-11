Connect(const char *addr, unsigned int port)
{
	assert(addr != NULL);

	sockaddr_in sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = inet_addr(addr);

	if (sa.sin_addr.s_addr == -1)
	{
		hostent *lphost = gethostbyname(addr);
		if (lphost == NULL)
		{
			SetLastError(SOCKET_EINVAL);
			CheckAndHandleError_int("gethostbyname", SOCKET_ERROR);
		}

		sa.sin_addr.s_addr = ((in_addr *)lphost->h_addr)->s_addr;
	}

	sa.sin_port = htons((u_short)port);

	return Connect((const sockaddr *)&sa, sizeof(sa));
}
