int Socket::connect(const std::string &ip, int port) {
    reset();

    if (sck < 0)
    {
        return -1;
    }

    int len = sizeof my_adr;
    peer_adr.sin_port = htons(port);
    inet_aton(ip.c_str(), &peer_adr.sin_addr);
    my_port = port;

    fcntl(sck, F_SETFL, O_NONBLOCK);
    s_errno = 0;
    errno = 0;
    int ret = ::connect(sck, (struct sockaddr *) &peer_adr, len);
    if (ret < 0 && errno == EINPROGRESS) ret = 0;
    else s_errno = errno;
    if (ret == 0) {
        int rc = poll(outfds, 1, timeout);
        if (rc == 0) {
            timedout = true;
            ret = -1;
        } else if (rc < 0) {
            s_errno = errno;
            ret = -1;
        } else {
            int so_error;
            socklen_t len = sizeof so_error;
            getsockopt(sck, SOL_SOCKET, SO_ERROR, &so_error, &len);
            if (so_error != 0) {
                sockerr = true;
                s_errno = so_error;
                ret = -1;
            } else {
                ret = 0;
            }
        }
    }
    fcntl(sck, F_SETFL, 0);
    if (ret < 0) close();
    return ret;
}
