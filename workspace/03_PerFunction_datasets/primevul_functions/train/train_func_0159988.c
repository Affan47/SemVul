intel_pmu_save_and_restart_reload(struct perf_event *event, int count)
{
	struct hw_perf_event *hwc = &event->hw;
	int shift = 64 - x86_pmu.cntval_bits;
	u64 period = hwc->sample_period;
	u64 prev_raw_count, new_raw_count;
	s64 new, old;

	WARN_ON(!period);


	WARN_ON(this_cpu_read(cpu_hw_events.enabled));

	prev_raw_count = local64_read(&hwc->prev_count);
	rdpmcl(hwc->event_base_rdpmc, new_raw_count);
	local64_set(&hwc->prev_count, new_raw_count);


	new = ((s64)(new_raw_count << shift) >> shift);
	old = ((s64)(prev_raw_count << shift) >> shift);
	local64_add(new - old + count * period, &event->count);

	local64_set(&hwc->period_left, -new);

	perf_event_update_userpage(event);

	return 0;
}
