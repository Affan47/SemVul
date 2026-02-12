static void bnx2x_period_task(struct work_struct *work)
{
	struct bnx2x *bp = container_of(work, struct bnx2x, period_task.work);

	if (!netif_running(bp->dev))
		goto period_task_exit;

	if (CHIP_REV_IS_SLOW(bp)) {
		BNX2X_ERR("period task called on emulation, ignoring\n");
		goto period_task_exit;
	}

	bnx2x_acquire_phy_lock(bp);


	smp_mb();
	if (bp->port.pmf) {
		bnx2x_period_func(&bp->link_params, &bp->link_vars);


		queue_delayed_work(bnx2x_wq, &bp->period_task, 1*HZ);
	}

	bnx2x_release_phy_lock(bp);
period_task_exit:
	return;
}
