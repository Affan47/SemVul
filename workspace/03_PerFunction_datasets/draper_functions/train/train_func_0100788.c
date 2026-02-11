gethinfo(int fd)
{
    int socksz;
    struct hostent *hent;
    char *iaddr;
    static char host[MAXHOSTNAMELEN];


    strcpy(host, "unknown-host");
    socksz = sizeof (struct sockaddr_in);
    if (getpeername(fd, (struct sockaddr *) &imspd_remoteaddr, &socksz) < 0) {
	return (NULL);
    }
    socksz = sizeof (struct sockaddr_in);
    getsockname(fd, (struct sockaddr *) &imspd_localaddr, &socksz);
    if ((iaddr = inet_ntoa(imspd_remoteaddr.sin_addr))) {
	strcpy(host, iaddr);
    }
    if ((hent = gethostbyaddr((char *) &imspd_remoteaddr.sin_addr,
			      sizeof (struct in_addr), AF_INET)) != NULL) {
	strcpy(host, hent->h_name);
    }

    return (host);
}
