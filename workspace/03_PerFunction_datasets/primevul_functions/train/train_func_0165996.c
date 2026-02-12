void zap_other_threads(struct task_struct *p)
{
	struct task_struct *t;

	p->signal->group_stop_count = 0;

	for (t = next_thread(p); t != p; t = next_thread(t)) {


		if (t->exit_state)
			continue;


		sigaddset(&t->pending.signal, SIGKILL);
		signal_wake_up(t, 1);
	}
}
