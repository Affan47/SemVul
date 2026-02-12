BPF_CALL_2(bpf_skb_pull_data, struct sk_buff *, skb, u32, len)
{


	return bpf_try_make_writable(skb, len ? : skb_headlen(skb));
}
