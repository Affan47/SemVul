static u64 update_triggers(struct psi_group *group, u64 now)
{
	struct psi_trigger *t;
	bool new_stall = false;
	u64 *total = group->total[PSI_POLL];


	list_for_each_entry(t, &group->triggers, node) {
		u64 growth;


		if (group->polling_total[t->state] == total[t->state])
			continue;


		new_stall = true;


		growth = window_update(&t->win, now, total[t->state]);
		if (growth < t->threshold)
			continue;


		if (now < t->last_event_time + t->win.size)
			continue;


		if (cmpxchg(&t->event, 0, 1) == 0)
			wake_up_interruptible(&t->event_wait);
		t->last_event_time = now;
	}

	if (new_stall)
		memcpy(group->polling_total, total,
				sizeof(group->polling_total));

	return now + group->poll_min_period;
}
