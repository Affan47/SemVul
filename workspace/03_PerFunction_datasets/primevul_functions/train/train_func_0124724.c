static gboolean discover_timeout(gpointer user_data)
{
	GDHCPClient *dhcp_client = user_data;

	dhcp_client->retry_times++;


	g_dhcp_client_start(dhcp_client, NULL);

	return FALSE;
}
