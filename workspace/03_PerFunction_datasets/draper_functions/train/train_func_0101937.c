g_dbus_client_unref(GDBusClient *client)
{
	unsigned int i;

	if (client == NULL)
		return;

	if (__sync_sub_and_fetch(&client->ref_count, 1) > 0)
		return;

	if (client->pending_call != NULL) {
		dbus_pending_call_cancel(client->pending_call);
		dbus_pending_call_unref(client->pending_call);
	}

	if (client->get_objects_call != NULL) {
		dbus_pending_call_cancel(client->get_objects_call);
		dbus_pending_call_unref(client->get_objects_call);
	}

	for (i = 0; i < client->match_rules->len; i++) {
		modify_match(client->dbus_conn, "RemoveMatch",
				g_ptr_array_index(client->match_rules, i));
	}

	g_ptr_array_free(client->match_rules, TRUE);

	dbus_connection_remove_filter(client->dbus_conn,
						message_filter, client);

	g_list_free_full(client->proxy_list, proxy_free);

	if (client->disconn_func)
		client->disconn_func(client->dbus_conn, client->disconn_data);

	dbus_connection_unref(client->dbus_conn);

	g_free(client->service_name);
	g_free(client->unique_name);
	g_free(client->base_path);

	g_free(client);
}
