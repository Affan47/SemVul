rfbReadExactTimeout(rfbClientPtr cl, char* buf, int len, int timeout)
{
    int sock = cl->sock;
    int n;
    fd_set fds;
    struct timeval tv;

    while (len > 0) {
        n = read(sock, buf, len);

        if (n > 0) {

            buf += n;
            len -= n;

        } else if (n == 0) {

            return 0;

        } else {
#ifdef WIN32
	    errno = WSAGetLastError();
#endif
	    if (errno == EINTR)
		continue;

#ifdef LIBVNCSERVER_ENOENT_WORKAROUND
	    if (errno != ENOENT)
#endif
            if (errno != EWOULDBLOCK && errno != EAGAIN) {
                return n;
            }

            FD_ZERO(&fds);
            FD_SET(sock, &fds);
            tv.tv_sec = timeout / 1000;
            tv.tv_usec = (timeout % 1000) * 1000;
            n = select(sock+1, &fds, NULL, &fds, &tv);
            if (n < 0) {
                rfbLogPerror("ReadExact: select");
                return n;
            }
            if (n == 0) {
                errno = ETIMEDOUT;
                return -1;
            }
        }
    }
#undef DEBUG_READ_EXACT
#ifdef DEBUG_READ_EXACT
    rfbLog("ReadExact %d bytes\n",len);
    for(n=0;n<len;n++)
	    fprintf(stderr,"%02x ",(unsigned char)buf[n]);
    fprintf(stderr,"\n");
#endif

    return 1;
}
