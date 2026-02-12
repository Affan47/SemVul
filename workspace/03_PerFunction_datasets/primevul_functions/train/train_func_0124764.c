static gboolean start_rebound(gpointer user_data)
{
	GDHCPClient *dhcp_client = user_data;


	if (dhcp_client->t1_timeout > 0)
		g_source_remove(dhcp_client->t1_timeout);

	debug(dhcp_client, "start rebound");
	dhcp_client->state = REBINDING;


	dhcp_client->T2 = dhcp_client->expire - dhcp_client->T2;


	continue_rebound(user_data);

	return FALSE;
}
