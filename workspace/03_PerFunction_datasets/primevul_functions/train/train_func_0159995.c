static void intel_pmu_pebs_event_update_no_drain(struct cpu_hw_events *cpuc, int size)
{
	struct perf_event *event;
	int bit;


	for_each_set_bit(bit, (unsigned long *)&cpuc->pebs_enabled, size) {
		event = cpuc->events[bit];
		if (event->hw.flags & PERF_X86_EVENT_AUTO_RELOAD)
			intel_pmu_save_and_restart_reload(event, 0);
	}
}
