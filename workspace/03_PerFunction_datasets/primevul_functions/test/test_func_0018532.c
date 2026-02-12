static void ovs_nla_free_clone_action(const struct nlattr *action)
{
	const struct nlattr *a = nla_data(action);
	int rem = nla_len(action);

	switch (nla_type(a)) {
	case OVS_CLONE_ATTR_EXEC:

		a = nla_next(a, &rem);
		ovs_nla_free_nested_actions(a, rem);
		break;
	}
}
