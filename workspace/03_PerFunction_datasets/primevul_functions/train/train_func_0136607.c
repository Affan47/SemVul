static void perf_pending_event_disable(struct perf_event *event)
{
	int cpu = READ_ONCE(event->pending_disable);

	if (cpu < 0)
		return;

	if (cpu == smp_processor_id()) {
		WRITE_ONCE(event->pending_disable, -1);
		perf_event_disable_local(event);
		return;
	}


	irq_work_queue_on(&event->pending, cpu);
}
