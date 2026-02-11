dlm_adjust_timeouts(struct dlm_ls *ls)
{
	struct dlm_lkb *lkb;
	u64 adj_us = jiffies_to_usecs(jiffies - ls->ls_recover_begin);

	ls->ls_recover_begin = 0;
	mutex_lock(&ls->ls_timeout_mutex);
	list_for_each_entry(lkb, &ls->ls_timeout, lkb_time_list)
		lkb->lkb_timestamp = ktime_add_us(lkb->lkb_timestamp, adj_us);
	mutex_unlock(&ls->ls_timeout_mutex);

	if (!dlm_config.ci_waitwarn_us)
		return;

	mutex_lock(&ls->ls_waiters_mutex);
	list_for_each_entry(lkb, &ls->ls_waiters, lkb_wait_reply) {
		if (ktime_to_us(lkb->lkb_wait_time))
			lkb->lkb_wait_time = ktime_get();
	}
	mutex_unlock(&ls->ls_waiters_mutex);
}
