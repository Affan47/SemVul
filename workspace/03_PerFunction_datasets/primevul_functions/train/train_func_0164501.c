switch_hrtimer_base(struct hrtimer *timer, struct hrtimer_clock_base *base)
{
	struct hrtimer_clock_base *new_base;
	struct hrtimer_cpu_base *new_cpu_base;

	new_cpu_base = &__get_cpu_var(hrtimer_bases);
	new_base = &new_cpu_base->clock_base[base->index];

	if (base != new_base) {


		if (unlikely(hrtimer_callback_running(timer)))
			return base;


		timer->base = NULL;
		spin_unlock(&base->cpu_base->lock);
		spin_lock(&new_base->cpu_base->lock);
		timer->base = new_base;
	}
	return new_base;
}
