static inline size_t rt6_nlmsg_size(void)
{
	return NLMSG_ALIGN(sizeof(struct rtmsg))
	       + nla_total_size(16)
	       + nla_total_size(16)
	       + nla_total_size(16)
	       + nla_total_size(16)
	       + nla_total_size(4)
	       + nla_total_size(4)
	       + nla_total_size(4)
	       + nla_total_size(4)
	       + RTAX_MAX * nla_total_size(4)
	       + nla_total_size(sizeof(struct rta_cacheinfo));
}
