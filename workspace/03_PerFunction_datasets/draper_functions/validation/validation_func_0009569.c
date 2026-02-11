xdmcp_client_get_local_address (XDMCPClient *client)
{
    GSocketAddress *socket_address;

    if (!client->priv->socket)
        return NULL;

    socket_address = g_socket_get_local_address (client->priv->socket, NULL);
    return g_inet_socket_address_get_address (G_INET_SOCKET_ADDRESS (socket_address));
}
