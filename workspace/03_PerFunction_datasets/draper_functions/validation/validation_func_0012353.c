ibus_bus_connect_async (IBusBus *bus)
{
    const gchar *bus_address = ibus_get_address ();

    if (bus_address == NULL)
        return;

    if (g_strcmp0 (bus->priv->bus_address, bus_address) == 0)
        return;


    ibus_bus_close_connection (bus);

    bus->priv->bus_address = g_strdup (bus_address);
    g_object_ref (bus);
    g_dbus_connection_new_for_address (
            bus_address,
            G_DBUS_CONNECTION_FLAGS_AUTHENTICATION_CLIENT |
            G_DBUS_CONNECTION_FLAGS_MESSAGE_BUS_CONNECTION,
            NULL,
            bus->priv->cancellable,
            _bus_connect_async_cb, bus);
}
