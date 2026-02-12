static size_t ovs_nsh_key_attr_size(void)
{


	return  nla_total_size(NSH_BASE_HDR_LEN)


		+ nla_total_size(NSH_CTX_HDRS_MAX_LEN);
}
