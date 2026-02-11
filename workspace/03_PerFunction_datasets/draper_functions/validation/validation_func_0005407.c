generic_unregister(DBusConnection *connection, void *user_data)
{
	struct generic_data *data = user_data;
	struct generic_data *parent = data->parent;

	if (parent != NULL)
		parent->objects = g_slist_remove(parent->objects, data);

	if (data->process_id > 0) {
		g_source_remove(data->process_id);
		process_changes(data);
	}

	g_slist_foreach(data->objects, reset_parent, data->parent);
	g_slist_free(data->objects);

	dbus_connection_unref(data->conn);
	g_free(data->introspect);
	g_free(data->path);
	g_free(data);
}
