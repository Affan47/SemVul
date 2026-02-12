static void power_pmu_read(struct perf_event *event)
{
	s64 val, delta, prev;

	if (event->hw.state & PERF_HES_STOPPED)
		return;

	if (!event->hw.idx)
		return;

	if (is_ebb_event(event)) {
		val = read_pmc(event->hw.idx);
		local64_set(&event->hw.prev_count, val);
		return;
	}


	do {
		prev = local64_read(&event->hw.prev_count);
		barrier();
		val = read_pmc(event->hw.idx);
		delta = check_and_compute_delta(prev, val);
		if (!delta)
			return;
	} while (local64_cmpxchg(&event->hw.prev_count, prev, val) != prev);

	local64_add(delta, &event->count);


	do {
		prev = local64_read(&event->hw.period_left);
		val = prev - delta;
		if (val < 1)
			val = 1;
	} while (local64_cmpxchg(&event->hw.period_left, prev, val) != prev);
}
