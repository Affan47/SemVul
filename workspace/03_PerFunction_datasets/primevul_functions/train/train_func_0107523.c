BPF_CALL_2(bpf_csum_update, struct sk_buff *, skb, __wsum, csum)
{


	if (skb->ip_summed == CHECKSUM_COMPLETE)
		return (skb->csum = csum_add(skb->csum, csum));

	return -ENOTSUPP;
}
