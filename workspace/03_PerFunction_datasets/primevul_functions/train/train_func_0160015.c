__intel_pmu_pebs_event(struct perf_event *event,
		       struct pt_regs *iregs,
		       struct perf_sample_data *data,
		       void *base, void *top,
		       int bit, int count,
		       void (*setup_sample)(struct perf_event *,
					    struct pt_regs *,
					    void *,
					    struct perf_sample_data *,
					    struct pt_regs *))
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct hw_perf_event *hwc = &event->hw;
	struct x86_perf_regs perf_regs;
	struct pt_regs *regs = &perf_regs.regs;
	void *at = get_next_pebs_record_by_bit(base, top, bit);
	static struct pt_regs dummy_iregs;

	if (hwc->flags & PERF_X86_EVENT_AUTO_RELOAD) {


		intel_pmu_save_and_restart_reload(event, count);
	} else if (!intel_pmu_save_and_restart(event))
		return;

	if (!iregs)
		iregs = &dummy_iregs;

	while (count > 1) {
		setup_sample(event, iregs, at, data, regs);
		perf_event_output(event, data, regs);
		at += cpuc->pebs_record_size;
		at = get_next_pebs_record_by_bit(at, top, bit);
		count--;
	}

	setup_sample(event, iregs, at, data, regs);
	if (iregs == &dummy_iregs) {


		perf_event_output(event, data, regs);
	} else {


		if (perf_event_overflow(event, data, regs))
			x86_pmu_stop(event, 0);
	}
}
