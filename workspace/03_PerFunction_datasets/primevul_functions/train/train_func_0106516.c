void tm_recheckpoint(struct thread_struct *thread)
{
	unsigned long flags;

	if (!(thread->regs->msr & MSR_TM))
		return;


	local_irq_save(flags);
	hard_irq_disable();


	tm_restore_sprs(thread);

	__tm_recheckpoint(thread);

	local_irq_restore(flags);
}
