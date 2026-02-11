intel_pstate_sample(struct cpudata *cpu)
{
	u64 aperf, mperf;
	unsigned long flags;
	u64 tsc;

	local_irq_save(flags);
	rdmsrl(MSR_IA32_APERF, aperf);
	rdmsrl(MSR_IA32_MPERF, mperf);
	if (cpu->prev_mperf == mperf) {
		local_irq_restore(flags);
		return;
	}

	tsc = rdtsc();
	local_irq_restore(flags);

	cpu->last_sample_time = cpu->sample.time;
	cpu->sample.time = ktime_get();
	cpu->sample.aperf = aperf;
	cpu->sample.mperf = mperf;
	cpu->sample.tsc =  tsc;
	cpu->sample.aperf -= cpu->prev_aperf;
	cpu->sample.mperf -= cpu->prev_mperf;
	cpu->sample.tsc -= cpu->prev_tsc;

	intel_pstate_calc_busy(cpu);

	cpu->prev_aperf = aperf;
	cpu->prev_mperf = mperf;
	cpu->prev_tsc = tsc;
}
