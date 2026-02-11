dns_sock_event_add(dns_sock_event_t *swait, dns_sock_t *sock)
{
    struct epoll_event event;

    memset(&event, 0, sizeof(event));
    event.events  = EPOLLIN | EPOLLET;
    event.data.ptr = sock;

    if (epoll_ctl(swait->sev_fd, EPOLL_CTL_ADD, sock->sock_fd, &event) < 0) {
        plog_error(LOG_ERR, MODULE, "epoll_ctl() failed");
        return -1;
    }

    plog(LOG_DEBUG, "%s: event add: fd = %d", MODULE, sock->sock_fd);

    return 0;
}
