__connman_counter_cleanup(void)
{
	DBG("");

	if (connection == NULL)
		return;

	g_hash_table_foreach(counter_table, release_counter, NULL);

	g_hash_table_destroy(owner_mapping);
	g_hash_table_destroy(counter_table);

	dbus_connection_unref(connection);
}
