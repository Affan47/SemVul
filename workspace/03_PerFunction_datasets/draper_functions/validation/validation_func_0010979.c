stop_queued_cmnd(struct scsi_cmnd *cmnd)
{
	unsigned long iflags;
	int k, qmax, r_qmax;
	struct sdebug_queued_cmd *sqcp;
	struct sdebug_dev_info *devip;

	spin_lock_irqsave(&queued_arr_lock, iflags);
	qmax = scsi_debug_max_queue;
	r_qmax = atomic_read(&retired_max_queue);
	if (r_qmax > qmax)
		qmax = r_qmax;
	for (k = 0; k < qmax; ++k) {
		if (test_bit(k, queued_in_use_bm)) {
			sqcp = &queued_arr[k];
			if (cmnd == sqcp->a_cmnd) {
				devip = (struct sdebug_dev_info *)
					cmnd->device->hostdata;
				if (devip)
					atomic_dec(&devip->num_in_q);
				sqcp->a_cmnd = NULL;
				spin_unlock_irqrestore(&queued_arr_lock,
						       iflags);
				if (scsi_debug_ndelay > 0) {
					if (sqcp->sd_hrtp)
						hrtimer_cancel(
							&sqcp->sd_hrtp->hrt);
				} else if (scsi_debug_delay > 0) {
					if (sqcp->cmnd_timerp)
						del_timer_sync(
							sqcp->cmnd_timerp);
				} else if (scsi_debug_delay < 0) {
					if (sqcp->tletp)
						tasklet_kill(sqcp->tletp);
				}
				clear_bit(k, queued_in_use_bm);
				return 1;
			}
		}
	}
	spin_unlock_irqrestore(&queued_arr_lock, iflags);
	return 0;
}
