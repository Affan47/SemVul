connman_agent_driver_unregister(struct connman_agent_driver *driver)
{
	GSList *list;

	if (driver == NULL)
		return;

	DBG("Unregistering driver %p name %s", driver, driver->name);

	if (agent_sender == NULL && agent_path == NULL)
		goto out;

	for (list = driver_list; list; list = list->next) {
		DBusMessage *message;

		if (driver != list->data)
			continue;

		DBG("Sending release to %s path %s iface %s", agent_sender,
			agent_path, driver->interface);

		message = dbus_message_new_method_call(agent_sender, agent_path,
				driver->interface, "Release");
		if (message != NULL) {
			dbus_message_set_no_reply(message, TRUE);
			g_dbus_send_message(connection, message);
		}

		agent_free();


		break;
	}

out:
	driver_list = g_slist_remove(driver_list, driver);
}
