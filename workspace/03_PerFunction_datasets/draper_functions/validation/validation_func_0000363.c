bind_socket(struct lbcd_config *config, socket_type **fds,
            unsigned int *count)
{
    int status;
    size_t i;
    const char *addr;


    status = sd_listen_fds(true);
    if (status < 0)
        die("using systemd-bound sockets failed: %s", strerror(-status));
    if (status > 0) {
        *fds = xcalloc(status, sizeof(socket_type));
        for (i = 0; i < (size_t) status; i++)
            (*fds)[i] = SD_LISTEN_FDS_START + i;
        *count = status;
        return;
    }


    if (config->bindaddrs->count == 0) {
        if (!network_bind_all(SOCK_DGRAM, config->port, fds, count))
            sysdie("cannot create UDP socket");
    } else {
        *count = config->bindaddrs->count;
        *fds = xcalloc(*count, sizeof(socket_type));
        for (i = 0; i < config->bindaddrs->count; i++) {
            addr = config->bindaddrs->strings[i];
            if (is_ipv6(addr))
                (*fds)[i] = network_bind_ipv6(SOCK_DGRAM, addr, config->port);
            else
                (*fds)[i] = network_bind_ipv4(SOCK_DGRAM, addr, config->port);
            if ((*fds)[i] == INVALID_SOCKET)
                sysdie("cannot bind to address %s, port %hu", addr,
                       config->port);
        }
    }
}
