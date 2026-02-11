ocrdma_post_srq_recv(struct ib_srq *ibsrq, struct ib_recv_wr *wr,
			 struct ib_recv_wr **bad_wr)
{
	int status = 0;
	unsigned long flags;
	struct ocrdma_srq *srq;
	struct ocrdma_hdr_wqe *rqe;
	u16 tag;

	srq = get_ocrdma_srq(ibsrq);

	spin_lock_irqsave(&srq->q_lock, flags);
	while (wr) {
		if (ocrdma_hwq_free_cnt(&srq->rq) == 0 ||
		    wr->num_sge > srq->rq.max_sges) {
			status = -ENOMEM;
			*bad_wr = wr;
			break;
		}
		tag = ocrdma_srq_get_idx(srq);
		rqe = ocrdma_hwq_head(&srq->rq);
		ocrdma_build_rqe(rqe, wr, tag);

		srq->rqe_wr_id_tbl[tag] = wr->wr_id;

		wmb();

		ocrdma_ring_srq_db(srq);

		ocrdma_hwq_inc_head(&srq->rq);
		wr = wr->next;
	}
	spin_unlock_irqrestore(&srq->q_lock, flags);
	return status;
}
