static int validate_and_copy_sample(struct net *net, const struct nlattr *attr,
				    const struct sw_flow_key *key,
				    struct sw_flow_actions **sfa,
				    __be16 eth_type, __be16 vlan_tci,
				    u32 mpls_label_count, bool log, bool last)
{
	const struct nlattr *attrs[OVS_SAMPLE_ATTR_MAX + 1];
	const struct nlattr *probability, *actions;
	const struct nlattr *a;
	int rem, start, err;
	struct sample_arg arg;

	memset(attrs, 0, sizeof(attrs));
	nla_for_each_nested(a, attr, rem) {
		int type = nla_type(a);
		if (!type || type > OVS_SAMPLE_ATTR_MAX || attrs[type])
			return -EINVAL;
		attrs[type] = a;
	}
	if (rem)
		return -EINVAL;

	probability = attrs[OVS_SAMPLE_ATTR_PROBABILITY];
	if (!probability || nla_len(probability) != sizeof(u32))
		return -EINVAL;

	actions = attrs[OVS_SAMPLE_ATTR_ACTIONS];
	if (!actions || (nla_len(actions) && nla_len(actions) < NLA_HDRLEN))
		return -EINVAL;


	start = add_nested_action_start(sfa, OVS_ACTION_ATTR_SAMPLE, log);
	if (start < 0)
		return start;


	arg.exec = last || !actions_may_change_flow(actions);
	arg.probability = nla_get_u32(probability);

	err = ovs_nla_add_action(sfa, OVS_SAMPLE_ATTR_ARG, &arg, sizeof(arg),
				 log);
	if (err)
		return err;

	err = __ovs_nla_copy_actions(net, actions, key, sfa,
				     eth_type, vlan_tci, mpls_label_count, log);

	if (err)
		return err;

	add_nested_action_end(*sfa, start);

	return 0;
}
