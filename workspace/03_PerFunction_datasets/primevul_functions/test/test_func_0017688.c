populate_action_info(struct respip_action_info* actinfo,
	enum respip_action action, const struct resp_addr* raddr,
	const struct ub_packed_rrset_key* ATTR_UNUSED(rrset),
	int ATTR_UNUSED(tag), const struct respip_set* ATTR_UNUSED(ipset),
	int ATTR_UNUSED(action_only), struct regional* region)
{
	if(action == respip_none || !raddr)
		return 1;
	actinfo->action = action;


	if(action == respip_inform || action == respip_inform_deny) {
		struct respip_addr_info* a =
			regional_alloc_zero(region, sizeof(*a));
		if(!a) {
			log_err("out of memory");
			return 0;
		}
		a->addr = raddr->node.addr;
		a->addrlen = raddr->node.addrlen;
		a->net = raddr->node.net;
		actinfo->addrinfo = a;
	}

	return 1;
}
