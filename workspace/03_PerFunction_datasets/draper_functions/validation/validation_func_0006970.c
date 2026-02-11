ck_activate_session (const gchar *cookie)
{
    GDBusConnection *bus;
    gchar *session_path;
    GError *error = NULL;

    g_return_if_fail (cookie != NULL);

    g_debug ("Activating ConsoleKit session %s", cookie);

    bus = g_bus_get_sync (G_BUS_TYPE_SYSTEM, NULL, &error);
    if (error)
        g_warning ("Failed to get system bus: %s", error->message);
    g_clear_error (&error);
    if (!bus)
        return;

    session_path = get_ck_session (bus, cookie);
    if (session_path)
    {
        GVariant *result;

        result = g_dbus_connection_call_sync (bus,
                                              "org.freedesktop.ConsoleKit",
                                              session_path,
                                              "org.freedesktop.ConsoleKit.Session",
                                              "Activate",
                                              g_variant_new ("()"),
                                              G_VARIANT_TYPE ("()"),
                                              G_DBUS_CALL_FLAGS_NONE,
                                              -1,
                                              NULL,
                                              &error);
        if (error)
            g_warning ("Error activating ConsoleKit session: %s", error->message);
        g_clear_error (&error);
        if (result)
            g_variant_unref (result);
    }
    g_object_unref (bus);
}
