ban_record(const host_addr_t addr, const char *msg)
{
	struct addr_info *ipf;
	struct ban *b = ban_object[BAN_CAT_SOCKET];

	ban_check(b);


	ipf = hevset_lookup(b->info, &addr);

	if (NULL == ipf) {
		ipf = ipf_make(addr, tm_time(), b);
		hevset_insert(b->info, ipf);
	}

	addr_info_check(ipf);

	atom_str_change(&ipf->ban_msg, msg);
	ipf->ban_delay = b->bantime;

	if (GNET_PROPERTY(ban_debug)) {
		g_debug("BAN %s %s record %s: %s",
			ban_category_string(b->cat),
			ipf->banned ? "updating" : "new",
			host_addr_to_string(ipf->addr), ban_reason(ipf));
	}

	if (ipf->banned)
		cq_resched(ipf->cq_ev, b->bantime * 1000);
	else {
		cq_cancel(&ipf->cq_ev);
		ipf->banned = TRUE;
		ipf->cq_ev = cq_insert(ban_cq, b->bantime * 1000, ipf_unban, ipf);
	}
}
