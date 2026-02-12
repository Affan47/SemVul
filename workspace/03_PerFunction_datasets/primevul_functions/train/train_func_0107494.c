static int __bpf_redirect_no_mac(struct sk_buff *skb, struct net_device *dev,
				 u32 flags)
{

	unsigned int mlen = skb->network_header - skb->mac_header;

	__skb_pull(skb, mlen);


	if (!skb_at_tc_ingress(skb))
		skb_postpull_rcsum(skb, skb_mac_header(skb), mlen);
	skb_pop_mac_header(skb);
	skb_reset_mac_len(skb);
	return flags & BPF_F_INGRESS ?
	       __bpf_rx_skb_no_mac(dev, skb) : __bpf_tx_skb(dev, skb);
}
