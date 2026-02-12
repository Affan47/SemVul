BPF_CALL_3(bpf_skb_change_head, struct sk_buff *, skb, u32, head_room,
	   u64, flags)
{
	u32 max_len = __bpf_skb_max_len(skb);
	u32 new_len = skb->len + head_room;
	int ret;

	if (unlikely(flags || (!skb_is_gso(skb) && new_len > max_len) ||
		     new_len < skb->len))
		return -EINVAL;

	ret = skb_cow(skb, head_room);
	if (likely(!ret)) {


		__skb_push(skb, head_room);
		memset(skb->data, 0, head_room);
		skb_reset_mac_header(skb);
	}

	bpf_compute_data_pointers(skb);
	return 0;
}
