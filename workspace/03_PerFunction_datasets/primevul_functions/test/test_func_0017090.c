static void del_timer_wait_running(struct timer_list *timer)
{
	u32 tf;

	tf = READ_ONCE(timer->flags);
	if (!(tf & TIMER_MIGRATING)) {
		struct timer_base *base = get_timer_base(tf);


		atomic_inc(&base->timer_waiters);
		spin_lock_bh(&base->expiry_lock);
		atomic_dec(&base->timer_waiters);
		spin_unlock_bh(&base->expiry_lock);
	}
}
