void bnx2x_init_ptp(struct bnx2x *bp)
{
	int rc;


	rc = bnx2x_configure_ptp(bp);
	if (rc) {
		BNX2X_ERR("Stopping PTP initialization\n");
		return;
	}


	INIT_WORK(&bp->ptp_task, bnx2x_ptp_task);


	if (!bp->timecounter_init_done) {
		bnx2x_init_cyclecounter(bp);
		timecounter_init(&bp->timecounter, &bp->cyclecounter,
				 ktime_to_ns(ktime_get_real()));
		bp->timecounter_init_done = 1;
	}

	DP(BNX2X_MSG_PTP, "PTP initialization ended successfully\n");
}
