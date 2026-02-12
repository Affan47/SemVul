static void free_pmu_context(struct pmu *pmu)
{


	if (pmu->task_ctx_nr > perf_invalid_context)
		return;

	free_percpu(pmu->pmu_cpu_context);
}
