int inet6_destroy_sock(struct sock *sk)
{
	struct ipv6_pinfo *np = inet6_sk(sk);
	struct sk_buff *skb;
	struct ipv6_txoptions *opt;


	if ((skb = xchg(&np->pktoptions, NULL)) != NULL)
		kfree_skb(skb);


	fl6_free_socklist(sk);


	if ((opt = xchg(&np->opt, NULL)) != NULL)
		sock_kfree_s(sk, opt, opt->tot_len);

	return 0;
}
