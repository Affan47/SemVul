do_getitimer(int which, struct itimerval *value)
{
	struct task_struct *tsk = current;

	switch (which) {
	case ITIMER_REAL:
		spin_lock_irq(&tsk->sighand->siglock);
		value->it_value = itimer_get_remtime(&tsk->signal->real_timer);
		value->it_interval =
			ktime_to_timeval(tsk->signal->it_real_incr);
		spin_unlock_irq(&tsk->sighand->siglock);
		break;
	case ITIMER_VIRTUAL:
		get_cpu_itimer(tsk, CPUCLOCK_VIRT, value);
		break;
	case ITIMER_PROF:
		get_cpu_itimer(tsk, CPUCLOCK_PROF, value);
		break;
	default:
		return(-EINVAL);
	}
	return 0;
}
