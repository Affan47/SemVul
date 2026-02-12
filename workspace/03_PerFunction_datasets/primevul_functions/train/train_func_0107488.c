BPF_CALL_3(bpf_skb_change_proto, struct sk_buff *, skb, __be16, proto,
	   u64, flags)
{
	int ret;

	if (unlikely(flags))
		return -EINVAL;


	ret = bpf_skb_proto_xlat(skb, proto);
	bpf_compute_data_pointers(skb);
	return ret;
}
