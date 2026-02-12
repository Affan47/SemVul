void release_ds_buffers(void)
{
	int cpu;

	if (!x86_pmu.bts && !x86_pmu.pebs)
		return;

	for_each_possible_cpu(cpu)
		release_ds_buffer(cpu);

	for_each_possible_cpu(cpu) {


		fini_debug_store_on_cpu(cpu);
	}

	for_each_possible_cpu(cpu) {
		release_pebs_buffer(cpu);
		release_bts_buffer(cpu);
	}
}
