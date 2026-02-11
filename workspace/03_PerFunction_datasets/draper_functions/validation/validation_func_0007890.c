up_device_removed_cb (DBusGProxy *proxy, const gchar *object_path, UpClient *client)
{
	UpDevice *device;
	device = up_client_get_device (client, object_path);
	if (device != NULL) {
		g_signal_emit (client, signals [UP_CLIENT_DEVICE_REMOVED], 0, device);
		g_ptr_array_remove (client->priv->array, device);
	}
}
