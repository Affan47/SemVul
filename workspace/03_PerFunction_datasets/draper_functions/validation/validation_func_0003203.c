close_connection(struct Connection *c) {

    if (c->state == CONNECTED || c->state == ACCEPTED || c->state == SERVER_CLOSED)
        close_client_connection(c);

    if (c->state == CONNECTED || c->state == CLIENT_CLOSED)
        close_server_connection(c);
}
