static int dhcp_recv_l2_packet(struct dhcp_packet *dhcp_pkt, int fd,
				struct sockaddr_in *dst_addr)
{
	int bytes;
	struct ip_udp_dhcp_packet packet;
	uint16_t check;

	memset(&packet, 0, sizeof(packet));

	bytes = read(fd, &packet, sizeof(packet));
	if (bytes < 0)
		return -1;

	if (bytes < (int) (sizeof(packet.ip) + sizeof(packet.udp)))
		return -1;

	if (bytes < ntohs(packet.ip.tot_len))

		return -1;


	bytes = ntohs(packet.ip.tot_len);

	if (!sanity_check(&packet, bytes))
		return -1;

	check = packet.ip.check;
	packet.ip.check = 0;
	if (check != dhcp_checksum(&packet.ip, sizeof(packet.ip)))
		return -1;


	memset(&packet.ip, 0, offsetof(struct iphdr, protocol));

	packet.ip.tot_len = packet.udp.len;
	check = packet.udp.check;
	packet.udp.check = 0;
	if (check && check != dhcp_checksum(&packet, bytes))
		return -1;

	memcpy(dhcp_pkt, &packet.data, bytes - (sizeof(packet.ip) +
							sizeof(packet.udp)));

	if (dhcp_pkt->cookie != htonl(DHCP_MAGIC))
		return -1;

	dst_addr->sin_addr.s_addr = packet.ip.daddr;

	return bytes - (sizeof(packet.ip) + sizeof(packet.udp));
}
