static int bpf_skb_net_grow(struct sk_buff *skb, u32 len_diff)
{
	u32 off = skb_mac_header_len(skb) + bpf_skb_net_base_len(skb);
	int ret;


	if (skb_is_gso(skb) && unlikely(skb_is_gso_sctp(skb)))
		return -ENOTSUPP;

	ret = skb_cow(skb, len_diff);
	if (unlikely(ret < 0))
		return ret;

	ret = bpf_skb_net_hdr_push(skb, off, len_diff);
	if (unlikely(ret < 0))
		return ret;

	if (skb_is_gso(skb)) {
		struct skb_shared_info *shinfo = skb_shinfo(skb);


		skb_decrease_gso_size(shinfo, len_diff);

		shinfo->gso_type |= SKB_GSO_DODGY;
		shinfo->gso_segs = 0;
	}

	return 0;
}
