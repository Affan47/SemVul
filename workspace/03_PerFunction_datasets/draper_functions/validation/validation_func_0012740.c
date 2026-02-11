pgsql_client(CLI *c, SERVICE_OPTIONS *opt, const PHASE phase) {
    u8 buffer[1];

    (void)opt;
    if(phase!=PROTOCOL_MIDDLE)
        return NULL;
    s_write(c, c->remote_fd.fd, ssl_request, sizeof ssl_request);
    s_read(c, c->remote_fd.fd, buffer, 1);

    if(buffer[0]!='S') {
        s_log(LOG_ERR, "PostgreSQL server rejected SSL");
        longjmp(c->err, 1);
    }
    return NULL;
}
