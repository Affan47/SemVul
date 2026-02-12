static int udp_queue_rcv_skb(struct sock * sk, struct sk_buff *skb)
{
	struct udp_sock *up = udp_sk(sk);
	int rc;


	if (!xfrm4_policy_check(sk, XFRM_POLICY_IN, skb)) {
		kfree_skb(skb);
		return -1;
	}
	nf_reset(skb);

	if (up->encap_type) {


		int ret;

		ret = udp_encap_rcv(sk, skb);
		if (ret == 0) {

			kfree_skb(skb);
			return 0;
		}
		if (ret < 0) {

			ret = xfrm4_rcv_encap(skb, up->encap_type);
			UDP_INC_STATS_BH(UDP_MIB_INDATAGRAMS);
			return -ret;
		}

	}

	if (sk->sk_filter && skb->ip_summed != CHECKSUM_UNNECESSARY) {
		if (__udp_checksum_complete(skb)) {
			UDP_INC_STATS_BH(UDP_MIB_INERRORS);
			kfree_skb(skb);
			return -1;
		}
		skb->ip_summed = CHECKSUM_UNNECESSARY;
	}

	if ((rc = sock_queue_rcv_skb(sk,skb)) < 0) {

		if (rc == -ENOMEM)
			UDP_INC_STATS_BH(UDP_MIB_RCVBUFERRORS);
		UDP_INC_STATS_BH(UDP_MIB_INERRORS);
		kfree_skb(skb);
		return -1;
	}
	UDP_INC_STATS_BH(UDP_MIB_INDATAGRAMS);
	return 0;
}
