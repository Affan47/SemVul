static int perf_event_read(struct perf_event *event, bool group)
{
	enum perf_event_state state = READ_ONCE(event->state);
	int event_cpu, ret = 0;


again:
	if (state == PERF_EVENT_STATE_ACTIVE) {
		struct perf_read_data data;


		smp_rmb();

		event_cpu = READ_ONCE(event->oncpu);
		if ((unsigned)event_cpu >= nr_cpu_ids)
			return 0;

		data = (struct perf_read_data){
			.event = event,
			.group = group,
			.ret = 0,
		};

		preempt_disable();
		event_cpu = __perf_event_read_cpu(event, event_cpu);


		(void)smp_call_function_single(event_cpu, __perf_event_read, &data, 1);
		preempt_enable();
		ret = data.ret;

	} else if (state == PERF_EVENT_STATE_INACTIVE) {
		struct perf_event_context *ctx = event->ctx;
		unsigned long flags;

		raw_spin_lock_irqsave(&ctx->lock, flags);
		state = event->state;
		if (state != PERF_EVENT_STATE_INACTIVE) {
			raw_spin_unlock_irqrestore(&ctx->lock, flags);
			goto again;
		}


		if (ctx->is_active & EVENT_TIME) {
			update_context_time(ctx);
			update_cgrp_time_from_event(event);
		}

		perf_event_update_time(event);
		if (group)
			perf_event_update_sibling_time(event);
		raw_spin_unlock_irqrestore(&ctx->lock, flags);
	}

	return ret;
}
