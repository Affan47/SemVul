BPF_CALL_1(bpf_get_hash_recalc, struct sk_buff *, skb)
{


	return skb_get_hash(skb);
}
