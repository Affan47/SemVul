static u64 cmp_next_hrtimer_event(u64 basem, u64 expires)
{
	u64 nextevt = hrtimer_get_next_event();


	if (expires <= nextevt)
		return expires;


	if (nextevt <= basem)
		return basem;


	return DIV_ROUND_UP_ULL(nextevt, TICK_NSEC) * TICK_NSEC;
}
