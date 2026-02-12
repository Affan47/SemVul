static int send_discover(GDHCPClient *dhcp_client, uint32_t requested)
{
	struct dhcp_packet packet;

	debug(dhcp_client, "sending DHCP discover request");

	init_packet(dhcp_client, &packet, DHCPDISCOVER);

	packet.xid = dhcp_client->xid;
	packet.secs = dhcp_attempt_secs(dhcp_client);

	if (requested)
		dhcp_add_option_uint32(&packet, DHCP_REQUESTED_IP, requested);


	dhcp_add_option_uint16(&packet, DHCP_MAX_SIZE, 576);

	add_request_options(dhcp_client, &packet);

	add_send_options(dhcp_client, &packet);


	dhcp_client->request_bcast = dhcp_client->retry_times % 2;

	if (dhcp_client->request_bcast)
		g_hash_table_add(dhcp_client->secs_bcast_hash,
				GINT_TO_POINTER(packet.secs));

	return dhcp_send_raw_packet(&packet, INADDR_ANY, CLIENT_PORT,
				INADDR_BROADCAST, SERVER_PORT,
				MAC_BCAST_ADDR, dhcp_client->ifindex,
				dhcp_client->request_bcast);
}
