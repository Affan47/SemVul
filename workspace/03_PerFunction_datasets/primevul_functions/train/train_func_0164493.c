static inline int hrtimer_enqueue_reprogram(struct hrtimer *timer,
					    struct hrtimer_clock_base *base)
{
	if (base->cpu_base->hres_active && hrtimer_reprogram(timer, base)) {


		switch(timer->cb_mode) {
		case HRTIMER_CB_IRQSAFE_NO_RESTART:


			BUG_ON(timer->function(timer) != HRTIMER_NORESTART);
			return 1;
		case HRTIMER_CB_IRQSAFE_NO_SOFTIRQ:


			return 1;
		case HRTIMER_CB_IRQSAFE:
		case HRTIMER_CB_SOFTIRQ:


			list_add_tail(&timer->cb_entry,
				      &base->cpu_base->cb_pending);
			timer->state = HRTIMER_STATE_PENDING;
			raise_softirq(HRTIMER_SOFTIRQ);
			return 1;
		default:
			BUG();
		}
	}
	return 0;
}
