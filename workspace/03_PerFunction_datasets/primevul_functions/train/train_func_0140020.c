static int bnx2x_enable_ptp_packets(struct bnx2x *bp)
{
	struct bnx2x_queue_state_params q_params;
	int rc, i;


	memset(&q_params, 0, sizeof(q_params));
	__set_bit(RAMROD_COMP_WAIT, &q_params.ramrod_flags);
	q_params.cmd = BNX2X_Q_CMD_UPDATE;
	__set_bit(BNX2X_Q_UPDATE_PTP_PKTS_CHNG,
		  &q_params.params.update.update_flags);
	__set_bit(BNX2X_Q_UPDATE_PTP_PKTS,
		  &q_params.params.update.update_flags);


	for_each_eth_queue(bp, i) {
		struct bnx2x_fastpath *fp = &bp->fp[i];


		q_params.q_obj = &bnx2x_sp_obj(bp, fp).q_obj;


		rc = bnx2x_queue_state_change(bp, &q_params);
		if (rc) {
			BNX2X_ERR("Failed to enable PTP packets\n");
			return rc;
		}
	}

	return 0;
}
