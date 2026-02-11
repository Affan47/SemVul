uhid_report_wake_up(struct uhid_device *uhid, u32 id,
				const struct uhid_event *ev)
{
	unsigned long flags;

	spin_lock_irqsave(&uhid->qlock, flags);


	if (uhid->report_type != ev->type || uhid->report_id != id)
		goto unlock;
	if (!uhid->report_running)
		goto unlock;

	memcpy(&uhid->report_buf, ev, sizeof(*ev));
	uhid->report_running = false;
	wake_up_interruptible(&uhid->report_wait);

unlock:
	spin_unlock_irqrestore(&uhid->qlock, flags);
}
