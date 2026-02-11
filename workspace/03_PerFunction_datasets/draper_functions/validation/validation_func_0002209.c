xdmcp_client_start (XDMCPClient *client)
{
    GSocketConnectable *address;
    GSocketAddressEnumerator *enumerator;
    gboolean result;
    GError *error = NULL;

    if (client->priv->socket)
        return TRUE;

    client->priv->socket = g_socket_new (G_SOCKET_FAMILY_IPV4, G_SOCKET_TYPE_DATAGRAM, G_SOCKET_PROTOCOL_UDP, &error);
    if (error)
        g_warning ("Error creating XDMCP socket: %s", error->message);
    g_clear_error (&error);
    if (!client->priv->socket)
        return FALSE;

    address = g_network_address_new (client->priv->host, client->priv->port);
    enumerator = g_socket_connectable_enumerate (address);
    result = FALSE;
    while (TRUE)
    {
        GSocketAddress *socket_address;
        GError *e = NULL;

        socket_address = g_socket_address_enumerator_next (enumerator, NULL, &e);
        if (e)
            g_warning ("Failed to get socket address: %s", e->message);
        g_clear_error (&e);
        if (!socket_address)
            break;

        result = g_socket_connect (client->priv->socket, socket_address, NULL, error ? NULL : &error);
        g_object_unref (socket_address);
        if (result)
        {
            g_clear_error (&error);
            break;
        }
    }
    if (error)
        g_warning ("Unable to connect XDMCP socket: %s", error->message);
    if (!result)
        return FALSE;

    g_io_add_watch (g_io_channel_unix_new (g_socket_get_fd (client->priv->socket)), G_IO_IN, xdmcp_data_cb, client);

    return TRUE;
}
