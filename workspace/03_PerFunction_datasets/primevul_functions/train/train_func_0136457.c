static void _perf_event_enable(struct perf_event *event)
{
	struct perf_event_context *ctx = event->ctx;

	raw_spin_lock_irq(&ctx->lock);
	if (event->state >= PERF_EVENT_STATE_INACTIVE ||
	    event->state <  PERF_EVENT_STATE_ERROR) {
out:
		raw_spin_unlock_irq(&ctx->lock);
		return;
	}


	if (event->state == PERF_EVENT_STATE_ERROR) {


		if (event->event_caps & PERF_EV_CAP_SIBLING &&
		    event->group_leader == event)
			goto out;

		event->state = PERF_EVENT_STATE_OFF;
	}
	raw_spin_unlock_irq(&ctx->lock);

	event_function_call(event, __perf_event_enable, NULL);
}
