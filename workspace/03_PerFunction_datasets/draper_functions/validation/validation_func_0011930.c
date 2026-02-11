tunnel_add_route()
{
	struct __connman_inet_rtnl_handle rth;
	struct in6_addr addr6;
	int index;
	int ret = 0;


	index = if_nametoindex("tun6to4");
	if (index == 0) {
		DBG("Can not find device tun6to4");
		return -1;
	}

	memset(&rth, 0, sizeof(rth));

	rth.req.n.nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg));
	rth.req.n.nlmsg_flags = NLM_F_REQUEST | NLM_F_CREATE | NLM_F_EXCL;
	rth.req.n.nlmsg_type = RTM_NEWROUTE;
	rth.req.u.r.rt.rtm_family = AF_INET6;
	rth.req.u.r.rt.rtm_table = RT_TABLE_MAIN;
	rth.req.u.r.rt.rtm_protocol = RTPROT_BOOT;
	rth.req.u.r.rt.rtm_scope = RT_SCOPE_UNIVERSE;
	rth.req.u.r.rt.rtm_type = RTN_UNICAST;
	rth.req.u.r.rt.rtm_dst_len = 0;

	inet_pton(AF_INET6, "::192.88.99.1", &addr6);

	__connman_inet_rtnl_addattr_l(&rth.req.n, sizeof(rth.req), RTA_GATEWAY,
					&addr6.s6_addr, 16);
	__connman_inet_rtnl_addattr32(&rth.req.n, sizeof(rth.req), RTA_OIF,
					index);
	__connman_inet_rtnl_addattr32(&rth.req.n, sizeof(rth.req),
					RTA_PRIORITY, 1);

	ret = __connman_inet_rtnl_open(&rth);
	if (ret < 0)
		goto done;

	ret = __connman_inet_rtnl_send(&rth, &rth.req.n);

done:
	__connman_inet_rtnl_close(&rth);
	return ret;
}
