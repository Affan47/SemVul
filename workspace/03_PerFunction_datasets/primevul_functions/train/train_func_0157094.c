static void mce_report_event(struct pt_regs *regs)
{
	if (regs->flags & (X86_VM_MASK|X86_EFLAGS_IF)) {
		mce_notify_irq();


		mce_schedule_work();
		return;
	}

	irq_work_queue(&mce_irq_work);
}
