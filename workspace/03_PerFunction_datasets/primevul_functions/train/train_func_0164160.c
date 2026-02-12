static inline size_t inet6_if_nlmsg_size(void)
{
	return NLMSG_ALIGN(sizeof(struct ifinfomsg))
	       + nla_total_size(IFNAMSIZ)
	       + nla_total_size(MAX_ADDR_LEN)
	       + nla_total_size(4)
	       + nla_total_size(4)
	       + nla_total_size(inet6_ifla6_size());
}
