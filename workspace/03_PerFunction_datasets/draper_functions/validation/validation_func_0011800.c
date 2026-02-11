nm_utils_complete_generic (NMConnection *connection,
                           const char *ctype,
                           const GSList *existing,
                           const char *format,
                           const char *preferred,
                           gboolean default_enable_ipv6)
{
	NMSettingConnection *s_con;
	NMSettingIP4Config *s_ip4;
	NMSettingIP6Config *s_ip6;
	const char *method;
	char *id, *uuid;

	s_con = nm_connection_get_setting_connection (connection);
	if (!s_con) {
		s_con = (NMSettingConnection *) nm_setting_connection_new ();
		nm_connection_add_setting (connection, NM_SETTING (s_con));
	}
	g_object_set (G_OBJECT (s_con), NM_SETTING_CONNECTION_TYPE, ctype, NULL);

	if (!nm_setting_connection_get_uuid (s_con)) {
		uuid = nm_utils_uuid_generate ();
		g_object_set (G_OBJECT (s_con), NM_SETTING_CONNECTION_UUID, uuid, NULL);
		g_free (uuid);
	}


	if (!nm_setting_connection_get_id (s_con)) {
		id = get_new_connection_name (existing, format, preferred);
		g_object_set (G_OBJECT (s_con), NM_SETTING_CONNECTION_ID, id, NULL);
		g_free (id);
	}


	s_ip4 = nm_connection_get_setting_ip4_config (connection);
	if (!s_ip4) {
		s_ip4 = (NMSettingIP4Config *) nm_setting_ip4_config_new ();
		nm_connection_add_setting (connection, NM_SETTING (s_ip4));
	}
	method = nm_setting_ip4_config_get_method (s_ip4);
	if (!method) {
		g_object_set (G_OBJECT (s_ip4),
		              NM_SETTING_IP4_CONFIG_METHOD, NM_SETTING_IP4_CONFIG_METHOD_AUTO,
		              NULL);
	}


	s_ip6 = nm_connection_get_setting_ip6_config (connection);
	if (!s_ip6 && default_enable_ipv6) {
		s_ip6 = (NMSettingIP6Config *) nm_setting_ip6_config_new ();
		nm_connection_add_setting (connection, NM_SETTING (s_ip6));
	}
	if (s_ip6 && !nm_setting_ip6_config_get_method (s_ip6)) {
		g_object_set (G_OBJECT (s_ip6),
		              NM_SETTING_IP6_CONFIG_METHOD, NM_SETTING_IP6_CONFIG_METHOD_AUTO,
		              NM_SETTING_IP6_CONFIG_MAY_FAIL, TRUE,
		              NULL);
	}
}
