lrmd_remote_client_destroy(gpointer user_data)
{
    crm_client_t *client = user_data;

    if (client == NULL) {
        return;
    }

    ipc_proxy_remove_provider(client);
    client_disconnect_cleanup(client->id);

    crm_notice("LRMD client disconnecting remote client - name: %s id: %s",
               client->name ? client->name : "<unknown>", client->id);

    if (client->remote->tls_session) {
        void *sock_ptr;
        int csock;

        sock_ptr = gnutls_transport_get_ptr(*client->remote->tls_session);
        csock = GPOINTER_TO_INT(sock_ptr);

        gnutls_bye(*client->remote->tls_session, GNUTLS_SHUT_RDWR);
        gnutls_deinit(*client->remote->tls_session);
        gnutls_free(client->remote->tls_session);
        close(csock);
    }

    crm_client_destroy(client);

    return;
}
