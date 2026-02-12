static int collect_expired_timers(struct timer_base *base,
				  struct hlist_head *heads)
{


	if ((long)(jiffies - base->clk) > 2) {
		unsigned long next = __next_timer_interrupt(base);


		if (time_after(next, jiffies)) {

			base->clk = jiffies - 1;
			return 0;
		}
		base->clk = next;
	}
	return __collect_expired_timers(base, heads);
}
