hcache_ht_get(hcache_class_t class, const host_addr_t addr, uint16 port,
	gnet_host_t **h, hostcache_entry_t **e)
{
	gnet_host_t host;
	const void *k;
	void *v;
	bool found;
	htable_t *ht;

	gnet_host_set(&host, addr, port);
	ht = hcache_ht_by_class(class);

	found = htable_lookup_extended(ht, &host, &k, &v);
	if (found) {
		*h = deconstify_pointer(k);
		*e = v;
	}

	return found;
}
