static int bnx2x_pf_flr_clnup(struct bnx2x *bp)
{
	u32 poll_cnt = bnx2x_flr_clnup_poll_count(bp);

	DP(BNX2X_MSG_SP, "Cleanup after FLR PF[%d]\n", BP_ABS_FUNC(bp));


	REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_TARGET_READ, 1);


	DP(BNX2X_MSG_SP, "Polling usage counters\n");
	if (bnx2x_poll_hw_usage_counters(bp, poll_cnt))
		return -EBUSY;


	if (bnx2x_send_final_clnup(bp, (u8)BP_FUNC(bp), poll_cnt))
		return -EBUSY;


	bnx2x_tx_hw_flushed(bp, poll_cnt);


	msleep(100);


	if (bnx2x_is_pcie_pending(bp->pdev))
		BNX2X_ERR("PCIE Transactions still pending\n");


	bnx2x_hw_enable_status(bp);


	REG_WR(bp, PGLUE_B_REG_INTERNAL_PFID_ENABLE_MASTER, 1);

	return 0;
}
