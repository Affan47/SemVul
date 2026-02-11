dht_ping(host_addr_t addr, uint16 port)
{
	knode_t *kn;
	vendor_code_t vc;
	static time_t last_sent = 0;
	time_t now = tm_time();


	if (!dht_is_active())
		return;


	if (delta_time(now, last_sent) < 60 || random_value(99) >= 10)
		return;

	last_sent = now;

	if (GNET_PROPERTY(dht_debug))
		g_debug("DHT randomly pinging host %s",
			host_addr_port_to_string(addr, port));


	vc.u32 = T_0000;
	kn = knode_new(&kuid_null, 0, addr, port, vc, 0, 0);


	dht_rpc_ping_extended(kn, RPC_CALL_NO_VERIFY, dht_ping_cb, NULL);
	knode_free(kn);
}
