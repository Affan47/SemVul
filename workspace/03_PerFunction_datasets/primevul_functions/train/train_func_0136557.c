long perf_pmu_snapshot_aux(struct perf_buffer *rb,
			   struct perf_event *event,
			   struct perf_output_handle *handle,
			   unsigned long size)
{
	unsigned long flags;
	long ret;


	local_irq_save(flags);


	WRITE_ONCE(rb->aux_in_sampling, 1);
	barrier();

	ret = event->pmu->snapshot_aux(event, handle, size);

	barrier();
	WRITE_ONCE(rb->aux_in_sampling, 0);
	local_irq_restore(flags);

	return ret;
}
