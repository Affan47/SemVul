linda_complete_send ( struct ib_device *ibdev,
				  struct ib_queue_pair *qp,
				  unsigned int wqe_idx ) {
	struct linda *linda = ib_get_drvdata ( ibdev );
	struct ib_work_queue *wq = &qp->send;
	struct linda_send_work_queue *linda_wq = ib_wq_get_drvdata ( wq );
	struct io_buffer *iobuf;
	unsigned int send_buf;


	send_buf = linda_wq->send_buf[wqe_idx];
	DBGC2 ( linda, "Linda %p QPN %ld TX %d(%d) complete\n",
		linda, qp->qpn, send_buf, wqe_idx );


	iobuf = wq->iobufs[wqe_idx];
	assert ( iobuf != NULL );
	ib_complete_send ( ibdev, qp, iobuf, 0 );
	wq->iobufs[wqe_idx] = NULL;


	linda_free_send_buf ( linda, send_buf );
}
