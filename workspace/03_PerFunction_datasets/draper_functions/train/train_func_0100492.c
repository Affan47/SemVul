download_send_udp_push(
	const struct array packet, host_addr_t addr, uint16 port)
{
	bool success = FALSE;

	if (host_is_valid(addr, port)) {
		struct gnutella_node *n;

		n = node_udp_get_addr_port(addr, port);
		if (n) {
			success = TRUE;
			udp_send_msg(n, packet.data, packet.size);
		}
	}
	return success;
}
