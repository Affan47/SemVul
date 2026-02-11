is_server_notification_ready(client_data* client) {
    int status = 0;
    fd_set ready_fdset;
    FD_ZERO(&ready_fdset);
    FD_SET(client->sock_fd, &ready_fdset);
    status = handle_select(client->sock_fd + 1, &ready_fdset, NULL, NULL);
    return status == 1;
}
