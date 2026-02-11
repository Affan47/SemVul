kmsg_send_mb(knode_t *kn, pmsg_t *mb)
{
	struct gnutella_node *n = node_dht_get_addr_port(kn->addr, kn->port);

	knode_check(kn);

	if (NULL == n) {

		if (GNET_PROPERTY(dht_debug)) {
			int len = pmsg_size(mb);
			g_debug("DHT discarding %s (%d bytes) to %s",
				kmsg_infostr(pmsg_start(mb)), len, knode_to_string(kn));
		}
		pmsg_free(mb);
		return;
	}

	if (GNET_PROPERTY(dht_debug) > 3) {
		int len = pmsg_size(mb);
		g_debug("DHT sending %s (%d bytes) to %s, RTT=%u",
			kmsg_infostr(pmsg_start(mb)), len, knode_to_string(kn), kn->rtt);
		if (GNET_PROPERTY(dht_trace) & SOCK_TRACE_OUT)
			dump_hex(stderr, "UDP datagram", pmsg_start(mb), len);
	}

	kn->last_sent = tm_time();
	udp_dht_send_mb(n, mb);
}
