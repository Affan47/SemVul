clusterip_tg(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct ipt_clusterip_tgt_info *cipinfo = par->targinfo;
	struct nf_conn *ct;
	enum ip_conntrack_info ctinfo;
	u_int32_t hash;


	ct = nf_ct_get(skb, &ctinfo);
	if (ct == NULL)
		return NF_DROP;


	if (ip_hdr(skb)->protocol == IPPROTO_ICMP &&
	    (ctinfo == IP_CT_RELATED ||
	     ctinfo == IP_CT_RELATED + IP_CT_IS_REPLY))
		return XT_CONTINUE;


	hash = clusterip_hashfn(skb, cipinfo->config);

	switch (ctinfo) {
		case IP_CT_NEW:
			ct->mark = hash;
			break;
		case IP_CT_RELATED:
		case IP_CT_RELATED+IP_CT_IS_REPLY:


		case IP_CT_ESTABLISHED:
		case IP_CT_ESTABLISHED+IP_CT_IS_REPLY:
			break;
		default:
			break;
	}

#ifdef DEBUG
	nf_ct_dump_tuple_ip(&ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
#endif
	pr_debug("hash=%u ct_hash=%u ", hash, ct->mark);
	if (!clusterip_responsible(cipinfo->config, hash)) {
		pr_debug("not responsible\n");
		return NF_DROP;
	}
	pr_debug("responsible\n");


	skb->pkt_type = PACKET_HOST;

	return XT_CONTINUE;
}
