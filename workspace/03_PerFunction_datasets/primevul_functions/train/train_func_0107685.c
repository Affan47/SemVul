BPF_CALL_2(bpf_set_hash, struct sk_buff *, skb, u32, hash)
{


	__skb_set_sw_hash(skb, hash, true);
	return 0;
}
