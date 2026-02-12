static void __netif_receive_skb_list_core(struct list_head *head, bool pfmemalloc)
{


	struct packet_type *pt_curr = NULL;

	struct net_device *od_curr = NULL;
	struct list_head sublist;
	struct sk_buff *skb, *next;

	INIT_LIST_HEAD(&sublist);
	list_for_each_entry_safe(skb, next, head, list) {
		struct net_device *orig_dev = skb->dev;
		struct packet_type *pt_prev = NULL;

		skb_list_del_init(skb);
		__netif_receive_skb_core(skb, pfmemalloc, &pt_prev);
		if (!pt_prev)
			continue;
		if (pt_curr != pt_prev || od_curr != orig_dev) {

			__netif_receive_skb_list_ptype(&sublist, pt_curr, od_curr);

			INIT_LIST_HEAD(&sublist);
			pt_curr = pt_prev;
			od_curr = orig_dev;
		}
		list_add_tail(&skb->list, &sublist);
	}


	__netif_receive_skb_list_ptype(&sublist, pt_curr, od_curr);
}
