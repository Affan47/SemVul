dump_ipaddress(void *if_data)
{
	ip_address_t *ipaddr = if_data;
	char *broadcast = (char *) MALLOC(INET_ADDRSTRLEN + 5);
	char *addr_str;

	addr_str = ipaddresstos(ipaddr);
	if (!IP_IS6(ipaddr) && ipaddr->u.sin.sin_brd.s_addr) {
		snprintf(broadcast, 21, " brd %s",
			 inet_ntop2(ipaddr->u.sin.sin_brd.s_addr));
	}

	log_message(LOG_INFO, "     %s/%d%s dev %s scope %s%s%s"
			    , addr_str
			    , ipaddr->ifa.ifa_prefixlen
			    , broadcast
			    , IF_NAME(ipaddr->ifp)
			    , netlink_scope_n2a(ipaddr->ifa.ifa_scope)
			    , ipaddr->label ? " label " : ""
			    , ipaddr->label ? ipaddr->label : "");
	FREE(broadcast);
	FREE(addr_str);
}
