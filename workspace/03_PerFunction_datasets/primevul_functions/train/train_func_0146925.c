void drain_all_pages(struct zone *zone)
{
	int cpu;


	static cpumask_t cpus_with_pcps;


	if (WARN_ON_ONCE(!mm_percpu_wq))
		return;


	if (current->flags & PF_WQ_WORKER)
		return;


	if (unlikely(!mutex_trylock(&pcpu_drain_mutex))) {
		if (!zone)
			return;
		mutex_lock(&pcpu_drain_mutex);
	}


	for_each_online_cpu(cpu) {
		struct per_cpu_pageset *pcp;
		struct zone *z;
		bool has_pcps = false;

		if (zone) {
			pcp = per_cpu_ptr(zone->pageset, cpu);
			if (pcp->pcp.count)
				has_pcps = true;
		} else {
			for_each_populated_zone(z) {
				pcp = per_cpu_ptr(z->pageset, cpu);
				if (pcp->pcp.count) {
					has_pcps = true;
					break;
				}
			}
		}

		if (has_pcps)
			cpumask_set_cpu(cpu, &cpus_with_pcps);
		else
			cpumask_clear_cpu(cpu, &cpus_with_pcps);
	}

	for_each_cpu(cpu, &cpus_with_pcps) {
		struct work_struct *work = per_cpu_ptr(&pcpu_drain, cpu);
		INIT_WORK(work, drain_local_pages_wq);
		queue_work_on(cpu, mm_percpu_wq, work);
	}
	for_each_cpu(cpu, &cpus_with_pcps)
		flush_work(per_cpu_ptr(&pcpu_drain, cpu));

	mutex_unlock(&pcpu_drain_mutex);
}
