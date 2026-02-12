static unsigned int selinux_ip_output(struct sk_buff *skb,
				      u16 family)
{
	struct sock *sk;
	u32 sid;

	if (!netlbl_enabled())
		return NF_ACCEPT;


	sk = skb->sk;
	if (sk) {
		struct sk_security_struct *sksec;

		if (sk->sk_state == TCP_LISTEN)


			return NF_ACCEPT;


		sksec = sk->sk_security;
		sid = sksec->sid;
	} else
		sid = SECINITSID_KERNEL;
	if (selinux_netlbl_skbuff_setsid(skb, family, sid) != 0)
		return NF_DROP;

	return NF_ACCEPT;
}
