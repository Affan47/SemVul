__acquires(&current->sighand->siglock)
{
	bool gstop_done = false;

	if (arch_ptrace_stop_needed(exit_code, info)) {


		spin_unlock_irq(&current->sighand->siglock);
		arch_ptrace_stop(exit_code, info);
		spin_lock_irq(&current->sighand->siglock);
		if (sigkill_pending(current))
			return;
	}

	set_special_state(TASK_TRACED);


	smp_wmb();

	current->last_siginfo = info;
	current->exit_code = exit_code;


	if (why == CLD_STOPPED && (current->jobctl & JOBCTL_STOP_PENDING))
		gstop_done = task_participate_group_stop(current);


	task_clear_jobctl_pending(current, JOBCTL_TRAP_STOP);
	if (info && info->si_code >> 8 == PTRACE_EVENT_STOP)
		task_clear_jobctl_pending(current, JOBCTL_TRAP_NOTIFY);


	task_clear_jobctl_trapping(current);

	spin_unlock_irq(&current->sighand->siglock);
	read_lock(&tasklist_lock);
	if (may_ptrace_stop()) {


		do_notify_parent_cldstop(current, true, why);
		if (gstop_done && ptrace_reparented(current))
			do_notify_parent_cldstop(current, false, why);


		preempt_disable();
		read_unlock(&tasklist_lock);
		cgroup_enter_frozen();
		preempt_enable_no_resched();
		freezable_schedule();
		cgroup_leave_frozen(true);
	} else {


		if (gstop_done)
			do_notify_parent_cldstop(current, false, why);


		__set_current_state(TASK_RUNNING);
		if (clear_code)
			current->exit_code = 0;
		read_unlock(&tasklist_lock);
	}


	spin_lock_irq(&current->sighand->siglock);
	current->last_siginfo = NULL;


	current->jobctl &= ~JOBCTL_LISTENING;


	recalc_sigpending_tsk(current);
}
