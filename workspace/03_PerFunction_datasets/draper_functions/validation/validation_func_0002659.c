o2hb_arm_write_timeout(struct o2hb_region *reg)
{

	if (atomic_read(&reg->hr_steady_iterations) != 0)
		return;

	mlog(ML_HEARTBEAT, "Queue write timeout for %u ms\n",
	     O2HB_MAX_WRITE_TIMEOUT_MS);

	if (o2hb_global_heartbeat_active()) {
		spin_lock(&o2hb_live_lock);
		clear_bit(reg->hr_region_num, o2hb_failed_region_bitmap);
		spin_unlock(&o2hb_live_lock);
	}
	cancel_delayed_work(&reg->hr_write_timeout_work);
	reg->hr_last_timeout_start = jiffies;
	schedule_delayed_work(&reg->hr_write_timeout_work,
			      msecs_to_jiffies(O2HB_MAX_WRITE_TIMEOUT_MS));
}
