void enable_kernel_vsx(void)
{
	unsigned long cpumsr;

	WARN_ON(preemptible());

	cpumsr = msr_check_and_set(MSR_FP|MSR_VEC|MSR_VSX);

	if (current->thread.regs &&
	    (current->thread.regs->msr & (MSR_VSX|MSR_VEC|MSR_FP))) {
		check_if_tm_restore_required(current);


		if (!MSR_TM_ACTIVE(cpumsr) &&
		     MSR_TM_ACTIVE(current->thread.regs->msr))
			return;
		__giveup_vsx(current);
	}
}
