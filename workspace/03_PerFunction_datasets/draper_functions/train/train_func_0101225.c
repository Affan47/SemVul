unregister_agent(DBusConnection *conn,
				DBusMessage *msg, void *data)
{
	struct audio_device *device = data;
	struct gateway *gw = device->gateway;
	const char *path;

	if (!gw->agent)
		goto done;

	if (strcmp(gw->agent->name, dbus_message_get_sender(msg)) != 0)
		return btd_error_not_authorized(msg);

	if (!dbus_message_get_args(msg, NULL,
				DBUS_TYPE_OBJECT_PATH, &path,
				DBUS_TYPE_INVALID))
		return btd_error_invalid_args(msg);

	if (strcmp(gw->agent->path, path) != 0)
		return btd_error_does_not_exist(msg);

	g_dbus_remove_watch(device->conn, gw->agent->watch);

	agent_free(gw->agent);
	gw->agent = NULL;

done:
	return dbus_message_new_method_return(msg);
}
