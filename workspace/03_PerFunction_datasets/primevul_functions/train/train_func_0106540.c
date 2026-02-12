void flush_fp_to_thread(struct task_struct *tsk)
{
	if (tsk->thread.regs) {


		preempt_disable();
		if (tsk->thread.regs->msr & MSR_FP) {


			BUG_ON(tsk != current);
			giveup_fpu(tsk);
		}
		preempt_enable();
	}
}
