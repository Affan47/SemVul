add_bss_to_network(struct supplicant_bss *bss)
{
	struct supplicant_interface *interface = bss->interface;
	struct supplicant_network *network;
	char *group;

	group = create_group(bss);
	if (group == NULL)
		return;

	network = g_hash_table_lookup(interface->network_table, group);
	if (network != NULL) {
		g_free(group);
		goto done;
	}

	network = g_try_new0(struct supplicant_network, 1);
	if (network == NULL) {
		g_free(group);
		return;
	}

	network->group = group;
	network->name = create_name(bss->ssid, bss->ssid_len);
	network->mode = bss->mode;

	network->bss_table = g_hash_table_new_full(g_str_hash, g_str_equal,
							NULL, remove_bss);

	network->config_table = g_hash_table_new_full(g_str_hash, g_str_equal,
							g_free, g_free);

	g_hash_table_replace(interface->network_table,
						network->group, network);

	callback_network_added(network);

done:
	g_hash_table_replace(interface->bss_mapping, bss->path, network);
	g_hash_table_replace(network->bss_table, bss->path, bss);

	g_hash_table_replace(bss_mapping, bss->path, interface);
}
