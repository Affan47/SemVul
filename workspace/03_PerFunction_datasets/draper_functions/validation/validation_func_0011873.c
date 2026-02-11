is_status_frame(struct sk_buff *skb, int type)
{
	struct ethhdr *h = eth_hdr(skb);

	if (PTP_CLASS_V2_L2 == type &&
	    !memcmp(h->h_source, status_frame_src, sizeof(status_frame_src)))
		return true;
	else
		return false;
}
