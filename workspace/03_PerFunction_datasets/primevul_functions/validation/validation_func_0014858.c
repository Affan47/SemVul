static size_t ctnetlink_nlmsg_size(const struct nf_conn *ct)
{
	return NLMSG_ALIGN(sizeof(struct nfgenmsg))
	       + 3 * nla_total_size(0)
	       + 3 * nla_total_size(0)
	       + 3 * nla_total_size(0)
	       + 3 * nla_total_size(sizeof(u_int8_t))
	       + nla_total_size(sizeof(u_int32_t))
	       + nla_total_size(sizeof(u_int32_t))
	       + ctnetlink_acct_size(ct)
	       + ctnetlink_timestamp_size(ct)
	       + nla_total_size(sizeof(u_int32_t))
	       + nla_total_size(0)
	       + nla_total_size(0)
	       + nla_total_size(NF_CT_HELPER_NAME_LEN)
	       + ctnetlink_secctx_size(ct)
#if IS_ENABLED(CONFIG_NF_NAT)
	       + 2 * nla_total_size(0)
	       + 6 * nla_total_size(sizeof(u_int32_t))
#endif
#ifdef CONFIG_NF_CONNTRACK_MARK
	       + nla_total_size(sizeof(u_int32_t))
#endif
#ifdef CONFIG_NF_CONNTRACK_ZONES
	       + nla_total_size(sizeof(u_int16_t))
#endif
	       + ctnetlink_proto_size(ct)
	       + ctnetlink_label_size(ct)
	       ;
}
