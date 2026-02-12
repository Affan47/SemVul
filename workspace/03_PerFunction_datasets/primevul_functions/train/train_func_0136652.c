static void perf_put_aux_event(struct perf_event *event)
{
	struct perf_event_context *ctx = event->ctx;
	struct perf_cpu_context *cpuctx = __get_cpu_context(ctx);
	struct perf_event *iter;


	if (event->aux_event) {
		iter = event->aux_event;
		event->aux_event = NULL;
		put_event(iter);
		return;
	}


	for_each_sibling_event(iter, event->group_leader) {
		if (iter->aux_event != event)
			continue;

		iter->aux_event = NULL;
		put_event(event);


		event_sched_out(iter, cpuctx, ctx);
		perf_event_set_state(event, PERF_EVENT_STATE_ERROR);
	}
}
