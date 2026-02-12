static void __aarp_resolved(struct aarp_entry **list, struct aarp_entry *a,
			    int hash)
{
	struct sk_buff *skb;

	while (*list)
		if (*list == a) {
			unresolved_count--;
			*list = a->next;


			a->next = resolved[hash];
			resolved[hash] = a;


			while ((skb = skb_dequeue(&a->packet_queue)) != NULL) {
				a->expires_at = jiffies +
						sysctl_aarp_expiry_time * 10;
				ddp_dl->request(ddp_dl, skb, a->hwaddr);
			}
		} else
			list = &((*list)->next);
}
