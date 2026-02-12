static int create_con_cq_qp(struct rtrs_clt_con *con)
{
	struct rtrs_clt_path *clt_path = to_clt_path(con->c.path);
	u32 max_send_wr, max_recv_wr, cq_num, max_send_sge, wr_limit;
	int err, cq_vector;
	struct rtrs_msg_rkey_rsp *rsp;

	lockdep_assert_held(&con->con_mutex);
	if (con->c.cid == 0) {
		max_send_sge = 1;

		if (WARN_ON(clt_path->s.dev))
			return -EINVAL;


		clt_path->s.dev = rtrs_ib_dev_find_or_add(con->c.cm_id->device,
						       &dev_pd);
		if (!clt_path->s.dev) {
			rtrs_wrn(clt_path->clt,
				  "rtrs_ib_dev_find_get_or_add(): no memory\n");
			return -ENOMEM;
		}
		clt_path->s.dev_ref = 1;
		query_fast_reg_mode(clt_path);
		wr_limit = clt_path->s.dev->ib_dev->attrs.max_qp_wr;


		max_send_wr =
			min_t(int, wr_limit, SERVICE_CON_QUEUE_DEPTH * 2 + 2);
		max_recv_wr = max_send_wr;
	} else {


		if (WARN_ON(!clt_path->s.dev))
			return -EINVAL;
		if (WARN_ON(!clt_path->queue_depth))
			return -EINVAL;

		wr_limit = clt_path->s.dev->ib_dev->attrs.max_qp_wr;

		clt_path->s.dev_ref++;
		max_send_wr = min_t(int, wr_limit,

			      clt_path->queue_depth * 3 + 1);
		max_recv_wr = min_t(int, wr_limit,
			      clt_path->queue_depth * 3 + 1);
		max_send_sge = 2;
	}
	atomic_set(&con->c.sq_wr_avail, max_send_wr);
	cq_num = max_send_wr + max_recv_wr;

	if (clt_path->flags & RTRS_MSG_NEW_RKEY_F || con->c.cid == 0) {
		con->rsp_ius = rtrs_iu_alloc(cq_num, sizeof(*rsp),
					      GFP_KERNEL,
					      clt_path->s.dev->ib_dev,
					      DMA_FROM_DEVICE,
					      rtrs_clt_rdma_done);
		if (!con->rsp_ius)
			return -ENOMEM;
		con->queue_num = cq_num;
	}
	cq_num = max_send_wr + max_recv_wr;
	cq_vector = con->cpu % clt_path->s.dev->ib_dev->num_comp_vectors;
	if (con->c.cid >= clt_path->s.irq_con_num)
		err = rtrs_cq_qp_create(&clt_path->s, &con->c, max_send_sge,
					cq_vector, cq_num, max_send_wr,
					max_recv_wr, IB_POLL_DIRECT);
	else
		err = rtrs_cq_qp_create(&clt_path->s, &con->c, max_send_sge,
					cq_vector, cq_num, max_send_wr,
					max_recv_wr, IB_POLL_SOFTIRQ);


	return err;
}
