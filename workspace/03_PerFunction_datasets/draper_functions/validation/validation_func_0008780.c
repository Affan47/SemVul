hfi1_alloc_lkey(struct hfi1_mregion *mr, int dma_region)
{
	unsigned long flags;
	u32 r;
	u32 n;
	int ret = 0;
	struct hfi1_ibdev *dev = to_idev(mr->pd->device);
	struct hfi1_lkey_table *rkt = &dev->lk_table;

	hfi1_get_mr(mr);
	spin_lock_irqsave(&rkt->lock, flags);


	if (dma_region) {
		struct hfi1_mregion *tmr;

		tmr = rcu_access_pointer(dev->dma_mr);
		if (!tmr) {
			rcu_assign_pointer(dev->dma_mr, mr);
			mr->lkey_published = 1;
		} else {
			hfi1_put_mr(mr);
		}
		goto success;
	}


	r = rkt->next;
	n = r;
	for (;;) {
		if (!rcu_access_pointer(rkt->table[r]))
			break;
		r = (r + 1) & (rkt->max - 1);
		if (r == n)
			goto bail;
	}
	rkt->next = (r + 1) & (rkt->max - 1);


	rkt->gen++;


	mr->lkey = (r << (32 - hfi1_lkey_table_size)) |
		((((1 << (24 - hfi1_lkey_table_size)) - 1) & rkt->gen)
		 << 8);
	if (mr->lkey == 0) {
		mr->lkey |= 1 << 8;
		rkt->gen++;
	}
	rcu_assign_pointer(rkt->table[r], mr);
	mr->lkey_published = 1;
success:
	spin_unlock_irqrestore(&rkt->lock, flags);
out:
	return ret;
bail:
	hfi1_put_mr(mr);
	spin_unlock_irqrestore(&rkt->lock, flags);
	ret = -ENOMEM;
	goto out;
}
