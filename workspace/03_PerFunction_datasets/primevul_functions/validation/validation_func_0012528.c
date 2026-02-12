static inline void perf_read_regs(struct pt_regs *regs)
{
	unsigned long mmcra = mfspr(SPRN_MMCRA);
	int marked = mmcra & MMCRA_SAMPLE_ENABLE;
	int use_siar;

	regs->dsisr = mmcra;

	if (ppmu->flags & PPMU_HAS_SIER)
		regs->dar = mfspr(SPRN_SIER);


	if (TRAP(regs) != INTERRUPT_PERFMON)
		use_siar = 0;
	else if ((ppmu->flags & PPMU_NO_SIAR))
		use_siar = 0;
	else if (marked)
		use_siar = 1;
	else if ((ppmu->flags & PPMU_NO_CONT_SAMPLING))
		use_siar = 0;
	else if (!(ppmu->flags & PPMU_NO_SIPR) && regs_sipr(regs))
		use_siar = 0;
	else
		use_siar = 1;

	regs->result = use_siar;
}
