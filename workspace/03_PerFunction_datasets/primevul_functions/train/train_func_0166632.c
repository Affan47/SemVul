static int tc_ctl_action(struct sk_buff *skb, struct nlmsghdr *n, void *arg)
{
	struct rtattr **tca = arg;
	u32 pid = skb ? NETLINK_CB(skb).pid : 0;
	int ret = 0, ovr = 0;

	if (tca[TCA_ACT_TAB-1] == NULL) {
		printk("tc_ctl_action: received NO action attribs\n");
		return -EINVAL;
	}


	switch (n->nlmsg_type) {
	case RTM_NEWACTION:


		if (n->nlmsg_flags&NLM_F_REPLACE)
			ovr = 1;
replay:
		ret = tcf_action_add(tca[TCA_ACT_TAB-1], n, pid, ovr);
		if (ret == -EAGAIN)
			goto replay;
		break;
	case RTM_DELACTION:
		ret = tca_action_gd(tca[TCA_ACT_TAB-1], n, pid, RTM_DELACTION);
		break;
	case RTM_GETACTION:
		ret = tca_action_gd(tca[TCA_ACT_TAB-1], n, pid, RTM_GETACTION);
		break;
	default:
		BUG();
	}

	return ret;
}
