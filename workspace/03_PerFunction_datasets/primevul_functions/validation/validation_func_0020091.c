
static void bfq_add_to_burst(struct bfq_data *bfqd, struct bfq_queue *bfqq)
{

	bfqd->burst_size++;

	if (bfqd->burst_size == bfqd->bfq_large_burst_thresh) {
		struct bfq_queue *pos, *bfqq_item;
		struct hlist_node *n;


		bfqd->large_burst = true;


		hlist_for_each_entry(bfqq_item, &bfqd->burst_list,
				     burst_list_node)
			bfq_mark_bfqq_in_large_burst(bfqq_item);
		bfq_mark_bfqq_in_large_burst(bfqq);


		hlist_for_each_entry_safe(pos, n, &bfqd->burst_list,
					  burst_list_node)
			hlist_del_init(&pos->burst_list_node);
	} else


		hlist_add_head(&bfqq->burst_list_node, &bfqd->burst_list);
}
