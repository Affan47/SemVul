dump_tx_tcp_packet(
	const struct gnutella_node *from, const struct gnutella_node *to,
	const pmsg_t *mb)
{
	if (GNET_PROPERTY(dump_transmitted_gnutella_packets)) {
		g_assert(to != NULL);
		g_assert(mb != NULL);
		g_assert(!NODE_IS_UDP(to));

		dump_packet_from_to(&dump_tx, from, to, mb);
	} else if (dump_tx.initialized) {
		dump_disable(&dump_tx);
	}
}
