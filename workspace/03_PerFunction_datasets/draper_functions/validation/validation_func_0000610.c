release_pebs_buffer(int cpu)
{
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;

	if (!ds || !x86_pmu.pebs)
		return;

	kfree(per_cpu(insn_buffer, cpu));
	per_cpu(insn_buffer, cpu) = NULL;

	dsfree((void *)(unsigned long)ds->pebs_buffer_base,
			x86_pmu.pebs_buffer_size);
	ds->pebs_buffer_base = 0;
}
