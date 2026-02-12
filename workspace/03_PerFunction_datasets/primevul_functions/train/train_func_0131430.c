ppp_receive_frame(struct ppp *ppp, struct sk_buff *skb, struct channel *pch)
{
	if (pskb_may_pull(skb, 2)) {
#ifdef CONFIG_PPP_MULTILINK

		if (PPP_PROTO(skb) == PPP_MP)
			ppp_receive_mp_frame(ppp, skb, pch);
		else
#endif
			ppp_receive_nonmp_frame(ppp, skb);
		return;
	}

	if (skb->len > 0)

		++ppp->dev->stats.rx_length_errors;

	kfree_skb(skb);
	ppp_receive_error(ppp);
}
