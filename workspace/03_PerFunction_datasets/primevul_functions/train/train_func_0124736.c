static gboolean reboot_timeout(gpointer user_data)
{
	GDHCPClient *dhcp_client = user_data;
	dhcp_client->retry_times = 0;
	dhcp_client->requested_ip = 0;
	dhcp_client->state = INIT_SELECTING;


	g_dhcp_client_start(dhcp_client, NULL);

	return FALSE;
}
