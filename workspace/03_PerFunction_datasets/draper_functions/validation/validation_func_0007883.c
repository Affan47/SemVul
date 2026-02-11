build_rdma_send(union t3_wr *wqe, struct ib_send_wr *wr,
				u8 * flit_cnt)
{
	int i;
	u32 plen;

	switch (wr->opcode) {
	case IB_WR_SEND:
		if (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.rdmaop = T3_SEND_WITH_SE;
		else
			wqe->send.rdmaop = T3_SEND;
		wqe->send.rem_stag = 0;
		break;
	case IB_WR_SEND_WITH_INV:
		if (wr->send_flags & IB_SEND_SOLICITED)
			wqe->send.rdmaop = T3_SEND_WITH_SE_INV;
		else
			wqe->send.rdmaop = T3_SEND_WITH_INV;
		wqe->send.rem_stag = cpu_to_be32(wr->ex.invalidate_rkey);
		break;
	default:
		return -EINVAL;
	}
	if (wr->num_sge > T3_MAX_SGE)
		return -EINVAL;
	wqe->send.reserved[0] = 0;
	wqe->send.reserved[1] = 0;
	wqe->send.reserved[2] = 0;
	plen = 0;
	for (i = 0; i < wr->num_sge; i++) {
		if ((plen + wr->sg_list[i].length) < plen)
			return -EMSGSIZE;

		plen += wr->sg_list[i].length;
		wqe->send.sgl[i].stag = cpu_to_be32(wr->sg_list[i].lkey);
		wqe->send.sgl[i].len = cpu_to_be32(wr->sg_list[i].length);
		wqe->send.sgl[i].to = cpu_to_be64(wr->sg_list[i].addr);
	}
	wqe->send.num_sgle = cpu_to_be32(wr->num_sge);
	*flit_cnt = 4 + ((wr->num_sge) << 1);
	wqe->send.plen = cpu_to_be32(plen);
	return 0;
}
