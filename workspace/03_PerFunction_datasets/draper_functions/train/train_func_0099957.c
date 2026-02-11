sim_properties_reply(struct modem_data *modem,
					DBusMessageIter *dict)
{
	DBG("%s", modem->path);

	while (dbus_message_iter_get_arg_type(dict) == DBUS_TYPE_DICT_ENTRY) {
		DBusMessageIter entry, value;
		const char *key;

		dbus_message_iter_recurse(dict, &entry);
		dbus_message_iter_get_basic(&entry, &key);

		dbus_message_iter_next(&entry);
		dbus_message_iter_recurse(&entry, &value);

		if (g_str_equal(key, "SubscriberIdentity") == TRUE) {
			sim_update_imsi(modem, &value);

			if (ready_to_create_device(modem) == FALSE)
				return;


			create_device(modem);

			if (modem->online == FALSE)
				return;


			if (has_interface(modem->interfaces, OFONO_API_CM) == TRUE) {
				cm_get_properties(modem);
				cm_get_contexts(modem);
			}
			return;
		}

		dbus_message_iter_next(dict);
	}
}
