builtin_security_function(DBusConnection *conn,
						const char *action,
						gboolean interaction,
						GDBusPendingReply pending)
{
	struct builtin_security_data *data;

	data = g_new0(struct builtin_security_data, 1);
	data->conn = conn;
	data->pending = pending;

	if (polkit_check_authorization(conn, action, interaction,
				builtin_security_result, data, 30000) < 0)
		g_dbus_pending_error(conn, pending, NULL, NULL);
}
