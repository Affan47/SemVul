_hash_with_username (NMConnection *connection, const char *username)
{
	NMConnection *dup;
	NMSettingVPN *s_vpn;
	GHashTable *hash;
	const char *existing;


	s_vpn = nm_connection_get_setting_vpn (connection);
	g_assert (s_vpn);
	existing = nm_setting_vpn_get_user_name (s_vpn);
	if (username == NULL || existing)
		return nm_connection_to_hash (connection, NM_SETTING_HASH_FLAG_ALL);

	dup = nm_connection_duplicate (connection);
	g_assert (dup);
	s_vpn = nm_connection_get_setting_vpn (dup);
	g_assert (s_vpn);
	g_object_set (s_vpn, NM_SETTING_VPN_USER_NAME, username, NULL);
	hash = nm_connection_to_hash (dup, NM_SETTING_HASH_FLAG_ALL);
	g_object_unref (dup);
	return hash;
}
