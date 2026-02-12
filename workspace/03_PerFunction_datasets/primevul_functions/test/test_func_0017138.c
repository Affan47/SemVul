static inline void forward_timer_base(struct timer_base *base)
{
#ifdef CONFIG_NO_HZ_COMMON
	unsigned long jnow;


	if (likely(!base->must_forward_clk))
		return;

	jnow = READ_ONCE(jiffies);
	base->must_forward_clk = base->is_idle;
	if ((long)(jnow - base->clk) < 2)
		return;


	if (time_after(base->next_expiry, jnow)) {
		base->clk = jnow;
	} else {
		if (WARN_ON_ONCE(time_before(base->next_expiry, base->clk)))
			return;
		base->clk = base->next_expiry;
	}
#endif
}
