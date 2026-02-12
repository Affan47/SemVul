static struct dst_entry *ip6_dst_check(struct dst_entry *dst, u32 cookie)
{
	struct rt6_info *rt;

	rt = (struct rt6_info *) dst;


	if (!rt->rt6i_node || (rt->rt6i_node->fn_sernum != cookie))
		return NULL;

	if (rt6_check_expired(rt))
		return NULL;

	return dst;
}
