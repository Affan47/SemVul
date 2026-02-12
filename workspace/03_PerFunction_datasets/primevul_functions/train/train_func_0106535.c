void restore_tm_state(struct pt_regs *regs)
{
	unsigned long msr_diff;


	clear_thread_flag(TIF_RESTORE_TM);
	if (!MSR_TM_ACTIVE(regs->msr))
		return;

	msr_diff = current->thread.ckpt_regs.msr & ~regs->msr;
	msr_diff &= MSR_FP | MSR_VEC | MSR_VSX;


	if (msr_diff & MSR_FP)
		current->thread.load_fp = 1;
#ifdef CONFIG_ALTIVEC
	if (cpu_has_feature(CPU_FTR_ALTIVEC) && msr_diff & MSR_VEC)
		current->thread.load_vec = 1;
#endif
	restore_math(regs);

	regs->msr |= msr_diff;
}
