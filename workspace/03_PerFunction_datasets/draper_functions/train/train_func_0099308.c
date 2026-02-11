interface_bss_removed(DBusMessageIter *iter, void *user_data)
{
	struct supplicant_interface *interface = user_data;
	struct supplicant_network *network;
	const char *path = NULL;

	dbus_message_iter_get_basic(iter, &path);
	if (path == NULL)
		return;

	network = g_hash_table_lookup(interface->bss_mapping, path);
	if (network == NULL)
		return;

	g_hash_table_remove(bss_mapping, path);

	g_hash_table_remove(interface->bss_mapping, path);
	g_hash_table_remove(network->bss_table, path);

	if (g_hash_table_size(network->bss_table) == 0)
		g_hash_table_remove(interface->network_table, network->group);
}
