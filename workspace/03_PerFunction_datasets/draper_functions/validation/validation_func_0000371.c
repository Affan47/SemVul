manager_create_session(DBusConnection *connection,
					struct test_session_info *info,
					const char *notifier_path)
{
	DBusMessage *message, *reply;
	DBusError error;
	DBusMessageIter array, dict;

	message = dbus_message_new_method_call(CONNMAN_SERVICE,
						CONNMAN_MANAGER_PATH,
						CONNMAN_MANAGER_INTERFACE,
							"CreateSession");
	if (message == NULL)
		return NULL;

	dbus_error_init(&error);

	dbus_message_iter_init_append(message, &array);

	connman_dbus_dict_open(&array, &dict);

	session_append_settings(&dict, info);

	connman_dbus_dict_close(&array, &dict);

	dbus_message_iter_append_basic(&array, DBUS_TYPE_OBJECT_PATH,
				&notifier_path);

	reply = dbus_connection_send_with_reply_and_block(connection,
							message, -1, &error);
	if (reply == NULL) {
		if (dbus_error_is_set(&error) == TRUE) {
			LOG("%s", error.message);
			dbus_error_free(&error);
		} else {
			LOG("Failed to get properties");
		}
		dbus_message_unref(message);
		return NULL;
	}

	dbus_message_unref(message);

	return reply;
}
