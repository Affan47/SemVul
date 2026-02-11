guess_alien_host(const guess_t *gq, const gnet_host_t *host, bool reached)
{
	if (GNET_PROPERTY(guess_client_debug) > 1) {
		g_info("GUESS QUERY[%s] host %s doesn't %s",
			nid_to_string(&gq->gid), gnet_host_to_string(host),
			reached ? "support GUESS" : "seem to be reachable");
	}


	aging_insert(guess_alien, atom_host_get(host), int_to_pointer(1));
	hcache_purge(HCACHE_CLASS_GUESS,
		gnet_host_get_addr(host), gnet_host_get_port(host));
	hevset_foreach(gqueries, guess_ignore_alien_host, deconstify_pointer(host));
}
