status_connect_cb (gpointer data)
{
    GSocket *socket;
    GError *error = NULL;

    socket = g_socket_accept (status_socket, NULL, &error);
    if (error)
        g_warning ("Failed to accept status connection: %s", error->message);
    g_clear_error (&error);
    if (socket)
    {
        StatusClient *client;

        client = g_malloc0 (sizeof (StatusClient));
        client->socket = socket;
        client->source = g_socket_create_source (socket, G_IO_IN, NULL);
        status_clients = g_list_append (status_clients, client);

        g_source_set_callback (client->source, (GSourceFunc) status_message_cb, client, NULL);
        g_source_attach (client->source, NULL);
    }

    return TRUE;
}
