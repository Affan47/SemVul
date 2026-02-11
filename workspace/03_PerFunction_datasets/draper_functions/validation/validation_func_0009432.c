add_cb (NMSettings *self,
        NMSettingsConnection *connection,
        GError *error,
        DBusGMethodInvocation *context,
        gpointer user_data)
{
	if (error)
		dbus_g_method_return_error (context, error);
	else
		dbus_g_method_return (context, nm_connection_get_path (NM_CONNECTION (connection)));
}
