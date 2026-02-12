static int ip_mc_check_igmp_query(struct sk_buff *skb)
{
	unsigned int transport_len = ip_transport_len(skb);
	unsigned int len;


	if (transport_len != sizeof(struct igmphdr)) {

		if (transport_len < sizeof(struct igmpv3_query))
			return -EINVAL;

		len = skb_transport_offset(skb) + sizeof(struct igmpv3_query);
		if (!ip_mc_may_pull(skb, len))
			return -EINVAL;
	}


	if (!igmp_hdr(skb)->group &&
	    ip_hdr(skb)->daddr != htonl(INADDR_ALLHOSTS_GROUP))
		return -EINVAL;

	return 0;
}
