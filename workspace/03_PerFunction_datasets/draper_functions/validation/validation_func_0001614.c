remove_network_cb (DBusGProxy *proxy, DBusGProxyCall *call_id, gpointer user_data)
{
	GError *error = NULL;

	if (!dbus_g_proxy_end_call (proxy, call_id, &error, G_TYPE_INVALID)) {
		nm_log_dbg (LOGD_SUPPLICANT, "Couldn't remove network from supplicant interface: %s.",
		             error && error->message ? error->message : "(unknown)");
		g_clear_error (&error);
	}
}
