comm_listen(int sock)
{
    int x;
    if ((x = listen(sock, Squid_MaxFD >> 2)) < 0) {
	debug(5, 0) ("comm_listen: listen(%d, %d): %s\n",
	    Squid_MaxFD >> 2,
	    sock, xstrerror());
	return x;
    }
    if (Config.accept_filter && strcmp(Config.accept_filter, "none") != 0) {
#ifdef SO_ACCEPTFILTER
	struct accept_filter_arg afa;
	bzero(&afa, sizeof(afa));
	debug(5, 0) ("Installing accept filter '%s' on FD %d\n",
	    Config.accept_filter, sock);
	xstrncpy(afa.af_name, Config.accept_filter, sizeof(afa.af_name));
	x = setsockopt(sock, SOL_SOCKET, SO_ACCEPTFILTER, &afa, sizeof(afa));
	if (x < 0)
	    debug(5, 0) ("SO_ACCEPTFILTER '%s': %s\n", Config.accept_filter, xstrerror());
#elif defined(TCP_DEFER_ACCEPT)
	int seconds = 30;
	if (strncmp(Config.accept_filter, "data=", 5) == 0)
	    seconds = atoi(Config.accept_filter + 5);
	x = setsockopt(sock, IPPROTO_TCP, TCP_DEFER_ACCEPT, &seconds, sizeof(seconds));
	if (x < 0)
	    debug(5, 0) ("TCP_DEFER_ACCEPT '%s': %s\n", Config.accept_filter, xstrerror());
#else
	debug(5, 0) ("accept_filter not supported on your OS\n");
#endif
    }
    return sock;
}
