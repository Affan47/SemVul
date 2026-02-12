static int perf_try_init_event(struct pmu *pmu, struct perf_event *event)
{
	struct perf_event_context *ctx = NULL;
	int ret;

	if (!try_module_get(pmu->module))
		return -ENODEV;


	if (event->group_leader != event && pmu->task_ctx_nr != perf_sw_context) {


		ctx = perf_event_ctx_lock_nested(event->group_leader,
						 SINGLE_DEPTH_NESTING);
		BUG_ON(!ctx);
	}

	event->pmu = pmu;
	ret = pmu->event_init(event);

	if (ctx)
		perf_event_ctx_unlock(event->group_leader, ctx);

	if (!ret) {
		if (!(pmu->capabilities & PERF_PMU_CAP_EXTENDED_REGS) &&
		    has_extended_regs(event))
			ret = -EOPNOTSUPP;

		if (pmu->capabilities & PERF_PMU_CAP_NO_EXCLUDE &&
		    event_has_any_exclude_flag(event))
			ret = -EINVAL;

		if (ret && event->destroy)
			event->destroy(event);
	}

	if (ret)
		module_put(pmu->module);

	return ret;
}
