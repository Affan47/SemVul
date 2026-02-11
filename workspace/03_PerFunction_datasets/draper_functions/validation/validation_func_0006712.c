get_system_bus (void)
{
        GError          *error;
        GDBusConnection *bus;

        error = NULL;
        bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);
        if (bus == NULL) {
                g_warning ("Couldn't connect to system bus: %s",
                           error->message);
                g_error_free (error);
                goto out;
        }

        g_signal_connect (bus, "closed",
                          G_CALLBACK (bus_connection_closed), NULL);
        g_dbus_connection_set_exit_on_close (bus, FALSE);

 out:
        return bus;
}
