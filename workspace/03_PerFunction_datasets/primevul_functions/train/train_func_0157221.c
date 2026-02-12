static inline struct sk_buff *skb_queue_prev(const struct sk_buff_head *list,
					     const struct sk_buff *skb)
{


	BUG_ON(skb_queue_is_first(list, skb));
	return skb->prev;
}
