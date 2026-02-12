static int dccp_msghdr_parse(struct msghdr *msg, struct sk_buff *skb)
{
	struct cmsghdr *cmsg;


	skb->priority = 0;

	for_each_cmsghdr(cmsg, msg) {
		if (!CMSG_OK(msg, cmsg))
			return -EINVAL;

		if (cmsg->cmsg_level != SOL_DCCP)
			continue;

		if (cmsg->cmsg_type <= DCCP_SCM_QPOLICY_MAX &&
		    !dccp_qpolicy_param_ok(skb->sk, cmsg->cmsg_type))
			return -EINVAL;

		switch (cmsg->cmsg_type) {
		case DCCP_SCM_PRIORITY:
			if (cmsg->cmsg_len != CMSG_LEN(sizeof(__u32)))
				return -EINVAL;
			skb->priority = *(__u32 *)CMSG_DATA(cmsg);
			break;
		default:
			return -EINVAL;
		}
	}
	return 0;
}
