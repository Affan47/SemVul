static void power_pmu_bhrb_disable(struct perf_event *event)
{
	struct cpu_hw_events *cpuhw = this_cpu_ptr(&cpu_hw_events);

	if (!ppmu->bhrb_nr)
		return;

	WARN_ON_ONCE(!cpuhw->bhrb_users);
	cpuhw->bhrb_users--;
	perf_sched_cb_dec(event->ctx->pmu);

	if (!cpuhw->disabled && !cpuhw->bhrb_users) {


		cpuhw->bhrb_context = NULL;
	}
}
