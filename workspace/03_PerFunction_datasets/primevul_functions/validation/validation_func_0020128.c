*/
void bfq_put_queue(struct bfq_queue *bfqq)
{
	struct bfq_queue *item;
	struct hlist_node *n;
	struct bfq_group *bfqg = bfqq_group(bfqq);

	if (bfqq->bfqd)
		bfq_log_bfqq(bfqq->bfqd, bfqq, "put_queue: %p %d",
			     bfqq, bfqq->ref);

	bfqq->ref--;
	if (bfqq->ref)
		return;

	if (!hlist_unhashed(&bfqq->burst_list_node)) {
		hlist_del_init(&bfqq->burst_list_node);


		if (bfqq->bic && bfqq->bfqd->burst_size > 0)
			bfqq->bfqd->burst_size--;
	}


	if (!hlist_unhashed(&bfqq->woken_list_node))
		hlist_del_init(&bfqq->woken_list_node);


	hlist_for_each_entry_safe(item, n, &bfqq->woken_list,
				  woken_list_node) {
		item->waker_bfqq = NULL;
		bfq_clear_bfqq_has_waker(item);
		hlist_del_init(&item->woken_list_node);
	}

	if (bfqq->bfqd && bfqq->bfqd->last_completed_rq_bfqq == bfqq)
		bfqq->bfqd->last_completed_rq_bfqq = NULL;

	kmem_cache_free(bfq_pool, bfqq);
	bfqg_and_blkg_put(bfqg);
}
