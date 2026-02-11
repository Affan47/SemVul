guess_host_added(void *u_data, void *hostinfo)
{
	struct hcache_new_host *nhost = hostinfo;

	(void) u_data;

	switch (nhost->type) {
	case HCACHE_GUESS:
	case HCACHE_GUESS_INTRO:
		break;
	default:
		return WQ_SLEEP;
	}


	if (hash_list_length(link_cache) >= GUESS_LINK_CACHE_SIZE) {
		guess_new_host_ev = NULL;
		return WQ_REMOVE;
	}


	{
		gnet_host_t host;
		gnet_host_set(&host, nhost->addr, nhost->port);
		if (hash_list_contains(link_cache, &host) || guess_should_skip(&host))
			return WQ_SLEEP;
	}


	if (hash_list_length(link_cache) < GUESS_LINK_CACHE_SIZE) {
		gnet_host_t host;

		gnet_host_set(&host, nhost->addr, nhost->port);
		if (!guess_request_qk(&host, TRUE))
			return WQ_SLEEP;
	}

	if (GNET_PROPERTY(guess_client_debug) > 1) {
		g_debug("GUESS discovered host %s",
			host_addr_port_to_string(nhost->addr, nhost->port));
	}


	return WQ_SLEEP;
}
