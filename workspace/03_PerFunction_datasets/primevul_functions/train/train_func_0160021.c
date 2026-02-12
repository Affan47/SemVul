static void intel_pmu_drain_pebs_nhm(struct pt_regs *iregs, struct perf_sample_data *data)
{
	struct cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	struct debug_store *ds = cpuc->ds;
	struct perf_event *event;
	void *base, *at, *top;
	short counts[INTEL_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = {};
	short error[INTEL_PMC_IDX_FIXED + MAX_FIXED_PEBS_EVENTS] = {};
	int bit, i, size;
	u64 mask;

	if (!x86_pmu.pebs_active)
		return;

	base = (struct pebs_record_nhm *)(unsigned long)ds->pebs_buffer_base;
	top = (struct pebs_record_nhm *)(unsigned long)ds->pebs_index;

	ds->pebs_index = ds->pebs_buffer_base;

	mask = (1ULL << x86_pmu.max_pebs_events) - 1;
	size = x86_pmu.max_pebs_events;
	if (x86_pmu.flags & PMU_FL_PEBS_ALL) {
		mask |= ((1ULL << x86_pmu.num_counters_fixed) - 1) << INTEL_PMC_IDX_FIXED;
		size = INTEL_PMC_IDX_FIXED + x86_pmu.num_counters_fixed;
	}

	if (unlikely(base >= top)) {
		intel_pmu_pebs_event_update_no_drain(cpuc, size);
		return;
	}

	for (at = base; at < top; at += x86_pmu.pebs_record_size) {
		struct pebs_record_nhm *p = at;
		u64 pebs_status;

		pebs_status = p->status & cpuc->pebs_enabled;
		pebs_status &= mask;


		if (x86_pmu.intel_cap.pebs_format >= 3) {
			for_each_set_bit(bit, (unsigned long *)&pebs_status, size)
				counts[bit]++;

			continue;
		}


		if (!pebs_status && cpuc->pebs_enabled &&
			!(cpuc->pebs_enabled & (cpuc->pebs_enabled-1)))
			pebs_status = p->status = cpuc->pebs_enabled;

		bit = find_first_bit((unsigned long *)&pebs_status,
					x86_pmu.max_pebs_events);
		if (bit >= x86_pmu.max_pebs_events)
			continue;


		if (pebs_status != (1ULL << bit)) {
			for_each_set_bit(i, (unsigned long *)&pebs_status, size)
				error[i]++;
			continue;
		}

		counts[bit]++;
	}

	for_each_set_bit(bit, (unsigned long *)&mask, size) {
		if ((counts[bit] == 0) && (error[bit] == 0))
			continue;

		event = cpuc->events[bit];
		if (WARN_ON_ONCE(!event))
			continue;

		if (WARN_ON_ONCE(!event->attr.precise_ip))
			continue;


		if (error[bit]) {
			perf_log_lost_samples(event, error[bit]);

			if (iregs && perf_event_account_interrupt(event))
				x86_pmu_stop(event, 0);
		}

		if (counts[bit]) {
			__intel_pmu_pebs_event(event, iregs, data, base,
					       top, bit, counts[bit],
					       setup_pebs_fixed_sample_data);
		}
	}
}
