static void ptrace_stop(int exit_code, int clear_code, siginfo_t *info)
{
	if (arch_ptrace_stop_needed(exit_code, info)) {


		spin_unlock_irq(&current->sighand->siglock);
		arch_ptrace_stop(exit_code, info);
		spin_lock_irq(&current->sighand->siglock);
		if (sigkill_pending(current))
			return;
	}


	if (current->signal->group_stop_count > 0)
		--current->signal->group_stop_count;

	current->last_siginfo = info;
	current->exit_code = exit_code;


	__set_current_state(TASK_TRACED);
	spin_unlock_irq(&current->sighand->siglock);
	read_lock(&tasklist_lock);
	if (may_ptrace_stop()) {
		do_notify_parent_cldstop(current, CLD_TRAPPED);


		preempt_disable();
		read_unlock(&tasklist_lock);
		preempt_enable_no_resched();
		schedule();
	} else {


		__set_current_state(TASK_RUNNING);
		if (clear_code)
			current->exit_code = 0;
		read_unlock(&tasklist_lock);
	}


	try_to_freeze();


	spin_lock_irq(&current->sighand->siglock);
	current->last_siginfo = NULL;


	recalc_sigpending_tsk(current);
}
