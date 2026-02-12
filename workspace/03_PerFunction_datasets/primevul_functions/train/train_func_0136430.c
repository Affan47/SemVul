static void account_event(struct perf_event *event)
{
	bool inc = false;

	if (event->parent)
		return;

	if (event->attach_state & PERF_ATTACH_TASK)
		inc = true;
	if (event->attr.mmap || event->attr.mmap_data)
		atomic_inc(&nr_mmap_events);
	if (event->attr.comm)
		atomic_inc(&nr_comm_events);
	if (event->attr.namespaces)
		atomic_inc(&nr_namespaces_events);
	if (event->attr.cgroup)
		atomic_inc(&nr_cgroup_events);
	if (event->attr.task)
		atomic_inc(&nr_task_events);
	if (event->attr.freq)
		account_freq_event();
	if (event->attr.context_switch) {
		atomic_inc(&nr_switch_events);
		inc = true;
	}
	if (has_branch_stack(event))
		inc = true;
	if (is_cgroup_event(event))
		inc = true;
	if (event->attr.ksymbol)
		atomic_inc(&nr_ksymbol_events);
	if (event->attr.bpf_event)
		atomic_inc(&nr_bpf_events);
	if (event->attr.text_poke)
		atomic_inc(&nr_text_poke_events);

	if (inc) {


		if (atomic_inc_not_zero(&perf_sched_count))
			goto enabled;

		mutex_lock(&perf_sched_mutex);
		if (!atomic_read(&perf_sched_count)) {
			static_branch_enable(&perf_sched_events);


			synchronize_rcu();
		}


		atomic_inc(&perf_sched_count);
		mutex_unlock(&perf_sched_mutex);
	}
enabled:

	account_event_cpu(event, event->cpu);

	account_pmu_sb_event(event);
}
