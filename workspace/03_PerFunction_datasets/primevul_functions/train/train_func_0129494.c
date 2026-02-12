static void __hrtimer_run_queues(struct hrtimer_cpu_base *cpu_base, ktime_t now)
{
	struct hrtimer_clock_base *base = cpu_base->clock_base;
	unsigned int active = cpu_base->active_bases;

	for (; active; base++, active >>= 1) {
		struct timerqueue_node *node;
		ktime_t basenow;

		if (!(active & 0x01))
			continue;

		basenow = ktime_add(now, base->offset);

		while ((node = timerqueue_getnext(&base->active))) {
			struct hrtimer *timer;

			timer = container_of(node, struct hrtimer, node);


			if (basenow < hrtimer_get_softexpires_tv64(timer))
				break;

			__run_hrtimer(cpu_base, base, timer, &basenow);
		}
	}
}
