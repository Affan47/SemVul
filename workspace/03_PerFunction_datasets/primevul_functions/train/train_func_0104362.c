static void gro_flush_oldest(struct list_head *head)
{
	struct sk_buff *oldest;

	oldest = list_last_entry(head, struct sk_buff, list);


	if (WARN_ON_ONCE(!oldest))
		return;


	skb_list_del_init(oldest);
	napi_gro_complete(oldest);
}
