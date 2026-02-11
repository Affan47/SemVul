event_filter_pid_sched_switch_probe_post(void *data, bool preempt,
		    struct task_struct *prev, struct task_struct *next)
{
	struct trace_array *tr = data;
	struct trace_pid_list *pid_list;

	pid_list = rcu_dereference_sched(tr->filtered_pids);

	this_cpu_write(tr->trace_buffer.data->ignore_pid,
		       check_ignore_pid(pid_list, next));
}
