request_cb(GDHCPClient *dhcp_client, gpointer user_data)
{
	DBG("");

	g_dhcpv6_client_clear_retransmit(dhcp_client);

	re_cb(dhcp_client, user_data);
}
