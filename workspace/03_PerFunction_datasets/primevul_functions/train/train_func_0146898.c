static int page_alloc_cpu_dead(unsigned int cpu)
{

	lru_add_drain_cpu(cpu);
	drain_pages(cpu);


	vm_events_fold_cpu(cpu);


	cpu_vm_stats_fold(cpu);
	return 0;
}
