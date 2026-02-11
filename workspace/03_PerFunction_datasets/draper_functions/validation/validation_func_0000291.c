log_connection(struct connection *cnx)
{
    struct addrinfo addr;
    struct sockaddr_storage ss;
#define MAX_NAMELENGTH (NI_MAXHOST + NI_MAXSERV + 1)
    char peer[MAX_NAMELENGTH], service[MAX_NAMELENGTH],
        local[MAX_NAMELENGTH], target[MAX_NAMELENGTH];
    int res;

    addr.ai_addr = (struct sockaddr*)&ss;
    addr.ai_addrlen = sizeof(ss);

    res = getpeername(cnx->q[0].fd, addr.ai_addr, &addr.ai_addrlen);
    if (res == -1) return;
    sprintaddr(peer, sizeof(peer), &addr);

    addr.ai_addrlen = sizeof(ss);
    res = getsockname(cnx->q[0].fd, addr.ai_addr, &addr.ai_addrlen);
    if (res == -1) return;
    sprintaddr(service, sizeof(service), &addr);

    addr.ai_addrlen = sizeof(ss);
    res = getpeername(cnx->q[1].fd, addr.ai_addr, &addr.ai_addrlen);
    if (res == -1) return;
    sprintaddr(target, sizeof(target), &addr);

    addr.ai_addrlen = sizeof(ss);
    res = getsockname(cnx->q[1].fd, addr.ai_addr, &addr.ai_addrlen);
    if (res == -1) return;
    sprintaddr(local, sizeof(local), &addr);

    log_message(LOG_INFO, "connection from %s to %s forwarded from %s to %s\n",
                peer,
                service,
                local,
                target);
}
