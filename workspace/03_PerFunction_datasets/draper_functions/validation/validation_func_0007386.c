sanei_tcp_open(const char *host, int port, int *fdp)
{
	int fd, err;
	struct sockaddr_in saddr;
	struct hostent *h;
#ifdef HAVE_WINSOCK2_H
	WSADATA wsaData;
#endif

	DBG_INIT();
	DBG(1, "%s: host = %s, port = %d\n", __FUNCTION__, host, port);

#ifdef HAVE_WINSOCK2_H
	err = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (err != 0)
	    return SANE_STATUS_INVAL;
#endif

	h = gethostbyname(host);

	if (h == NULL || h->h_addr_list[0] == NULL
	    || h->h_addrtype != AF_INET)
		return SANE_STATUS_INVAL;

	if ((fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
		return SANE_STATUS_INVAL;

	memset(&saddr, 0x00, sizeof(struct sockaddr_in));

	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	memcpy(&saddr.sin_addr, h->h_addr_list[0], h->h_length);

	if ((err =
	     connect(fd, (struct sockaddr *) &saddr,
		     sizeof(struct sockaddr_in))) != 0) {
		close(fd);
		return SANE_STATUS_INVAL;
	}

	*fdp = fd;

	return SANE_STATUS_GOOD;
}
