bc_handler(struct hrtimer *t)
{
	ce_broadcast_hrtimer.event_handler(&ce_broadcast_hrtimer);

	if (clockevent_state_oneshot(&ce_broadcast_hrtimer))
		if (ce_broadcast_hrtimer.next_event.tv64 != KTIME_MAX)
			return HRTIMER_RESTART;

	return HRTIMER_NORESTART;
}
