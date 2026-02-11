dns_sock_init(void)
{
    dns_util_sasetport((SA *) &Options.opt_baddr, Options.opt_port);

    if (dns_sock_event_init(&SockEventUdp) < 0)
        return -1;
    if (dns_sock_event_init(&SockEventTcp) < 0)
        return -1;

    if (sock_listen(SOCK_DGRAM, (SA *) &Options.opt_baddr) < 0)
        return -1;
    if (sock_listen(SOCK_STREAM, (SA *) &Options.opt_baddr) < 0)
        return -1;

    return 0;
}
