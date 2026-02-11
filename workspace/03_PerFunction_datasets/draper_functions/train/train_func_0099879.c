toggle_watch(DBusWatch *watch, void *data)
{

	if (dbus_watch_get_enabled(watch))
		remove_watch(watch, data);
	else
		add_watch(watch, data);
}
