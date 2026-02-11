proxy_free(gpointer data)
{
	GDBusProxy *proxy = data;

	if (proxy->client) {
		GDBusClient *client = proxy->client;

		if (client->proxy_removed)
			client->proxy_removed(proxy, client->user_data);

		modify_match(client->dbus_conn, "RemoveMatch",
							proxy->match_rule);

		g_free(proxy->match_rule);
		proxy->match_rule = NULL;

		g_hash_table_remove_all(proxy->prop_list);

		proxy->client = NULL;
	}

	if (proxy->removed_func)
		proxy->removed_func(proxy, proxy->removed_data);

	g_dbus_proxy_unref(proxy);
}
