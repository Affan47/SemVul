static inline struct sk_buff *skb_queue_next(const struct sk_buff_head *list,
					     const struct sk_buff *skb)
{


	BUG_ON(skb_queue_is_last(list, skb));
	return skb->next;
}
