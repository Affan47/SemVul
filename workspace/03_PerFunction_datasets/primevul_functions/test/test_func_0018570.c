size_t ovs_key_attr_size(void)
{


	BUILD_BUG_ON(OVS_KEY_ATTR_MAX != 32);

	return    nla_total_size(4)
		+ nla_total_size(0)
		  + ovs_tun_key_attr_size()
		+ nla_total_size(4)
		+ nla_total_size(4)
		+ nla_total_size(4)
		+ nla_total_size(4)
		+ nla_total_size(4)
		+ nla_total_size(2)
		+ nla_total_size(4)
		+ nla_total_size(16)
		+ nla_total_size(40)
		+ nla_total_size(0)
		  + ovs_nsh_key_attr_size()
		+ nla_total_size(12)
		+ nla_total_size(2)
		+ nla_total_size(4)
		+ nla_total_size(0)
		+ nla_total_size(2)
		+ nla_total_size(40)
		+ nla_total_size(2)
		+ nla_total_size(28)
		+ nla_total_size(2);
}
