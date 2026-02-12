perf_event_set_state(struct perf_event *event, enum perf_event_state state)
{
	if (event->state == state)
		return;

	perf_event_update_time(event);


	if ((event->state < 0) ^ (state < 0))
		perf_event_update_sibling_time(event);

	WRITE_ONCE(event->state, state);
}
