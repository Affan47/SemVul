ocrdma_poll_success_rcqe(struct ocrdma_qp *qp,
				     struct ocrdma_cqe *cqe, struct ib_wc *ibwc)
{
	ibwc->opcode = IB_WC_RECV;
	ibwc->qp = &qp->ibqp;
	ibwc->status = IB_WC_SUCCESS;

	if (qp->qp_type == IB_QPT_UD || qp->qp_type == IB_QPT_GSI)
		ocrdma_update_ud_rcqe(ibwc, cqe);
	else
		ibwc->byte_len = le32_to_cpu(cqe->rq.rxlen);

	if (is_cqe_imm(cqe)) {
		ibwc->ex.imm_data = htonl(le32_to_cpu(cqe->rq.lkey_immdt));
		ibwc->wc_flags |= IB_WC_WITH_IMM;
	} else if (is_cqe_wr_imm(cqe)) {
		ibwc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
		ibwc->ex.imm_data = htonl(le32_to_cpu(cqe->rq.lkey_immdt));
		ibwc->wc_flags |= IB_WC_WITH_IMM;
	} else if (is_cqe_invalidated(cqe)) {
		ibwc->ex.invalidate_rkey = le32_to_cpu(cqe->rq.lkey_immdt);
		ibwc->wc_flags |= IB_WC_WITH_INVALIDATE;
	}
	if (qp->ibqp.srq) {
		ocrdma_update_free_srq_cqe(ibwc, cqe, qp);
	} else {
		ibwc->wr_id = qp->rqe_wr_id_tbl[qp->rq.tail];
		ocrdma_hwq_inc_tail(&qp->rq);
	}
}
