BPF_CALL_1(bpf_set_hash_invalid, struct sk_buff *, skb)
{


	skb_clear_hash(skb);
	return 0;
}
