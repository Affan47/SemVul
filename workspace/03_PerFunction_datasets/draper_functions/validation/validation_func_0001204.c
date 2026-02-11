add_activate_cb (DBusGProxy *proxy,
                 DBusGProxyCall *call,
                 gpointer user_data)
{
	ActivateInfo *info = user_data;
	char *connection_path;
	char *active_path;
	GError *error = NULL;

	dbus_g_proxy_end_call (proxy, call, &error,
	                       DBUS_TYPE_G_OBJECT_PATH, &connection_path,
	                       DBUS_TYPE_G_OBJECT_PATH, &active_path,
	                       G_TYPE_INVALID);
	if (error) {
		activate_info_complete (info, NULL, error);
		activate_info_free (info);
	} else {
		info->new_connection_path = connection_path;
		info->active_path = active_path;
		recheck_pending_activations (info->client, NULL, NULL);
	}
}
