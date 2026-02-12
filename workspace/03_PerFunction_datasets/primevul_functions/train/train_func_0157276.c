static inline void skb_forward_csum(struct sk_buff *skb)
{

	if (skb->ip_summed == CHECKSUM_COMPLETE)
		skb->ip_summed = CHECKSUM_NONE;
}
