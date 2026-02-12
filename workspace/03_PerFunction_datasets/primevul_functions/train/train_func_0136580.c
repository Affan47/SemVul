static void perf_event_context_sched_in(struct perf_event_context *ctx,
					struct task_struct *task)
{
	struct perf_cpu_context *cpuctx;
	struct pmu *pmu = ctx->pmu;

	cpuctx = __get_cpu_context(ctx);
	if (cpuctx->task_ctx == ctx) {
		if (cpuctx->sched_cb_usage)
			__perf_pmu_sched_task(cpuctx, true);
		return;
	}

	perf_ctx_lock(cpuctx, ctx);


	if (!ctx->nr_events)
		goto unlock;

	perf_pmu_disable(pmu);


	if (!RB_EMPTY_ROOT(&ctx->pinned_groups.tree))
		cpu_ctx_sched_out(cpuctx, EVENT_FLEXIBLE);
	perf_event_sched_in(cpuctx, ctx, task);

	if (cpuctx->sched_cb_usage && pmu->sched_task)
		pmu->sched_task(cpuctx->task_ctx, true);

	perf_pmu_enable(pmu);

unlock:
	perf_ctx_unlock(cpuctx, ctx);
}
