udp_ping_register(const struct guid *muid,
	host_addr_t addr, uint16 port,
	udp_ping_cb_t cb, void *data, bool multiple)
{
	struct udp_ping *ping;
	uint length;

	g_assert(muid);
	g_return_val_if_fail(udp_pings, FALSE);

	if (hash_list_contains(udp_pings, muid)) {

		return FALSE;
	}


	length = hash_list_length(udp_pings);
	if (length >= UDP_PING_MAX) {
		return FALSE;
	} else if (length > (UDP_PING_MAX / 4) * 3) {
		if (random_value(UDP_PING_MAX - 1) < length)
			return FALSE;
	}

	WALLOC(ping);
	ping->muid = *muid;
	ping->added = tm_time();
	{
		gnet_host_t host;
		gnet_host_set(&host, addr, port);
		ping->host = atom_host_get(&host);
	}

	if (cb != NULL) {
		WALLOC0(ping->callback);
		ping->callback->cb = cb;
		ping->callback->data = data;
		ping->callback->multiple = booleanize(multiple);
	} else {
		ping->callback = NULL;
	}
	hash_list_append(udp_pings, ping);
	return TRUE;
}
