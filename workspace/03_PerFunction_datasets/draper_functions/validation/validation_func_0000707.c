connect (int sockfd, const struct sockaddr *addr, socklen_t addrlen)
{
    int port, redirected_port;
    const struct sockaddr *modified_addr = addr;
    struct sockaddr_in temp_addr;
    struct sockaddr_in6 temp_addr6;
    int (*_connect) (int sockfd, const struct sockaddr *addr, socklen_t addrlen);

    _connect = (int (*)(int sockfd, const struct sockaddr *addr, socklen_t addrlen)) dlsym (RTLD_NEXT, "connect");

    switch (addr->sa_family)
    {
    case AF_INET:
        port = ntohs (((const struct sockaddr_in *) addr)->sin_port);
        redirected_port = find_port_redirect (port);
        if (redirected_port != 0)
        {
            memcpy (&temp_addr, addr, sizeof (struct sockaddr_in));
            temp_addr.sin_port = htons (redirected_port);
            modified_addr = (struct sockaddr *) &temp_addr;
        }
        break;
    case AF_INET6:
        port = ntohs (((const struct sockaddr_in6 *) addr)->sin6_port);
        redirected_port = find_port_redirect (port);
        if (redirected_port != 0)
        {
            memcpy (&temp_addr6, addr, sizeof (struct sockaddr_in6));
            temp_addr6.sin6_port = htons (redirected_port);
            modified_addr = (struct sockaddr *) &temp_addr6;
        }
        break;
    }

    return _connect (sockfd, modified_addr, addrlen);
}
