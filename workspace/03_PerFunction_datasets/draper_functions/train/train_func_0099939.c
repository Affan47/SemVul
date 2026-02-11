dht_bootstrap(host_addr_t addr, uint16 port)
{


	if (dht_is_bootstrapping())
		return;

	if (GNET_PROPERTY(dht_debug))
		g_debug("DHT attempting bootstrap from %s",
			host_addr_port_to_string(addr, port));

	dht_probe(addr, port);
}
