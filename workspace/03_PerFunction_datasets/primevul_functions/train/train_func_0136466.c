void perf_event_disable_inatomic(struct perf_event *event)
{
	WRITE_ONCE(event->pending_disable, smp_processor_id());

	irq_work_queue(&event->pending);
}
