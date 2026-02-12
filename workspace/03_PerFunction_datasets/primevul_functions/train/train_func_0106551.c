void enable_kernel_altivec(void)
{
	unsigned long cpumsr;

	WARN_ON(preemptible());

	cpumsr = msr_check_and_set(MSR_VEC);

	if (current->thread.regs && (current->thread.regs->msr & MSR_VEC)) {
		check_if_tm_restore_required(current);


		if (!MSR_TM_ACTIVE(cpumsr) &&
		     MSR_TM_ACTIVE(current->thread.regs->msr))
			return;
		__giveup_altivec(current);
	}
}
