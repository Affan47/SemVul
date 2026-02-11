http_init(char *proxy)
{
	char *host, *port;
#ifdef WIN32
	WSADATA wsadata;
	if (!WSAStartup(MAKEWORD(2,2), &wsadata))
		http_up = 1;
#else
	signal(SIGPIPE, SIG_IGN);
	http_up = 1;
#endif
	if (proxy)
	{
		host = getserv(proxy);
		port = getport(proxy);
		if (resolve(host, port, &http_proxy))
			http_up = 0;
		else
			http_use_proxy = 1;
		free(host);
		free(port);
	}
}
