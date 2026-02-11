hfi1_rkey_ok(struct hfi1_qp *qp, struct hfi1_sge *sge,
		 u32 len, u64 vaddr, u32 rkey, int acc)
{
	struct hfi1_lkey_table *rkt = &to_idev(qp->ibqp.device)->lk_table;
	struct hfi1_mregion *mr;
	unsigned n, m;
	size_t off;


	rcu_read_lock();
	if (rkey == 0) {
		struct hfi1_pd *pd = to_ipd(qp->ibqp.pd);
		struct hfi1_ibdev *dev = to_idev(pd->ibpd.device);

		if (pd->user)
			goto bail;
		mr = rcu_dereference(dev->dma_mr);
		if (!mr)
			goto bail;
		atomic_inc(&mr->refcount);
		rcu_read_unlock();

		sge->mr = mr;
		sge->vaddr = (void *) vaddr;
		sge->length = len;
		sge->sge_length = len;
		sge->m = 0;
		sge->n = 0;
		goto ok;
	}

	mr = rcu_dereference(
		rkt->table[(rkey >> (32 - hfi1_lkey_table_size))]);
	if (unlikely(!mr || mr->lkey != rkey || qp->ibqp.pd != mr->pd))
		goto bail;

	off = vaddr - mr->iova;
	if (unlikely(vaddr < mr->iova || off + len > mr->length ||
		     (mr->access_flags & acc) == 0))
		goto bail;
	atomic_inc(&mr->refcount);
	rcu_read_unlock();

	off += mr->offset;
	if (mr->page_shift) {


		size_t entries_spanned_by_off;

		entries_spanned_by_off = off >> mr->page_shift;
		off -= (entries_spanned_by_off << mr->page_shift);
		m = entries_spanned_by_off / HFI1_SEGSZ;
		n = entries_spanned_by_off % HFI1_SEGSZ;
	} else {
		m = 0;
		n = 0;
		while (off >= mr->map[m]->segs[n].length) {
			off -= mr->map[m]->segs[n].length;
			n++;
			if (n >= HFI1_SEGSZ) {
				m++;
				n = 0;
			}
		}
	}
	sge->mr = mr;
	sge->vaddr = mr->map[m]->segs[n].vaddr + off;
	sge->length = mr->map[m]->segs[n].length - off;
	sge->sge_length = len;
	sge->m = m;
	sge->n = n;
ok:
	return 1;
bail:
	rcu_read_unlock();
	return 0;
}
