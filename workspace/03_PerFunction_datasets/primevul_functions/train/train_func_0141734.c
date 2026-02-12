static size_t ovs_flow_cmd_msg_size(const struct sw_flow_actions *acts)
{
	return NLMSG_ALIGN(sizeof(struct ovs_header))
		+ nla_total_size(key_attr_size())
		+ nla_total_size(key_attr_size())
		+ nla_total_size(sizeof(struct ovs_flow_stats))
		+ nla_total_size(1)
		+ nla_total_size(8)
		+ nla_total_size(acts->actions_len);
}
