get_best_auto_connection (NMModem *modem,
                          GSList *connections,
                          char **specific_object)
{
	GSList *iter;

	for (iter = connections; iter; iter = g_slist_next (iter)) {
		NMConnection *connection = NM_CONNECTION (iter->data);

		if (nm_connection_is_type (connection, NM_SETTING_CDMA_SETTING_NAME))
			return connection;
	}
	return NULL;
}
