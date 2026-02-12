static inline u32 perf_get_misc_flags(struct pt_regs *regs)
{
	bool use_siar = regs_use_siar(regs);
	unsigned long mmcra = regs->dsisr;
	int marked = mmcra & MMCRA_SAMPLE_ENABLE;

	if (!use_siar)
		return perf_flags_from_msr(regs);


	if (marked && (ppmu->flags & PPMU_P10_DD1)) {
		unsigned long siar = mfspr(SPRN_SIAR);
		if (siar) {
			if (is_kernel_addr(siar))
				return PERF_RECORD_MISC_KERNEL;
			return PERF_RECORD_MISC_USER;
		} else {
			if (is_kernel_addr(regs->nip))
				return PERF_RECORD_MISC_KERNEL;
			return PERF_RECORD_MISC_USER;
		}
	}


	if (ppmu->flags & PPMU_NO_SIPR) {
		unsigned long siar = mfspr(SPRN_SIAR);
		if (is_kernel_addr(siar))
			return PERF_RECORD_MISC_KERNEL;
		return PERF_RECORD_MISC_USER;
	}


	if (regs_sipr(regs))
		return PERF_RECORD_MISC_USER;

	if (regs_sihv(regs) && (freeze_events_kernel != MMCR0_FCHV))
		return PERF_RECORD_MISC_HYPERVISOR;

	return PERF_RECORD_MISC_KERNEL;
}
