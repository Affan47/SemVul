rfbAcceptUnixSocket(int sock)
{
#ifdef WIN32
    rfbLog("Windows doesn't support UNIX sockets\n");
    return -1;
#else
    struct sockaddr_un addr;
    int fd, fromlen = sizeof(addr);

    fd = accept(sock, (struct sockaddr *)&addr, &fromlen);
    if (fd < 0) {
	rfbLogPerror("rfbAcceptUnixSocket: accept failed");
	return -1;
    }
    return fd;
#endif
}
