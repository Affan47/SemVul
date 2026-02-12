static int bpf_skb_generic_push(struct sk_buff *skb, u32 off, u32 len)
{


	skb_push(skb, len);
	memmove(skb->data, skb->data + len, off);
	memset(skb->data + off, 0, len);


	return 0;
}
