list_add_event(struct perf_event *event, struct perf_event_context *ctx)
{
	lockdep_assert_held(&ctx->lock);

	WARN_ON_ONCE(event->attach_state & PERF_ATTACH_CONTEXT);
	event->attach_state |= PERF_ATTACH_CONTEXT;

	event->tstamp = perf_event_time(event);


	if (event->group_leader == event) {
		event->group_caps = event->event_caps;
		add_event_to_groups(event, ctx);
	}

	list_add_rcu(&event->event_entry, &ctx->event_list);
	ctx->nr_events++;
	if (event->attr.inherit_stat)
		ctx->nr_stat++;

	if (event->state > PERF_EVENT_STATE_OFF)
		perf_cgroup_event_enable(event, ctx);

	ctx->generation++;
}
