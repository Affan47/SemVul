pebs_update_state(bool needed_cb, struct cpu_hw_events *cpuc,
		  struct perf_event *event, bool add)
{
	struct pmu *pmu = event->ctx->pmu;


	bool update = cpuc->n_pebs == 1;

	if (needed_cb != pebs_needs_sched_cb(cpuc)) {
		if (!needed_cb)
			perf_sched_cb_inc(pmu);
		else
			perf_sched_cb_dec(pmu);

		update = true;
	}


	if (x86_pmu.intel_cap.pebs_baseline && add) {
		u64 pebs_data_cfg;


		if (cpuc->n_pebs == 1) {
			cpuc->pebs_data_cfg = 0;
			cpuc->pebs_record_size = sizeof(struct pebs_basic);
		}

		pebs_data_cfg = pebs_update_adaptive_cfg(event);


		if (pebs_data_cfg & ~cpuc->pebs_data_cfg) {
			cpuc->pebs_data_cfg |= pebs_data_cfg;
			adaptive_pebs_record_size_update();
			update = true;
		}
	}

	if (update)
		pebs_update_threshold(cpuc);
}
