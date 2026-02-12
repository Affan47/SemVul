static int collect_expired_timers(struct timer_base *base,
				  struct hlist_head *heads)
{
	unsigned long now = READ_ONCE(jiffies);


	if ((long)(now - base->clk) > 2) {
		unsigned long next = __next_timer_interrupt(base);


		if (time_after(next, now)) {


			base->clk = now;
			return 0;
		}
		base->clk = next;
	}
	return __collect_expired_timers(base, heads);
}
