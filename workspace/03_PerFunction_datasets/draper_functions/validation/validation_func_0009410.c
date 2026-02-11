lease6_exists(const struct ipv6_pool *pool, const struct in6_addr *addr) {
	struct iasubopt *test_iaaddr;

	test_iaaddr = NULL;
	if (iasubopt_hash_lookup(&test_iaaddr, pool->leases,
				 (void *)addr, sizeof(*addr), MDL)) {
		iasubopt_dereference(&test_iaaddr, MDL);
		return ISC_TRUE;
	} else {
		return ISC_FALSE;
	}
}
