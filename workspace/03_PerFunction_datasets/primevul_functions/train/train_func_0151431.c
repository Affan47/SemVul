u64 ring_buffer_event_time_stamp(struct trace_buffer *buffer,
				 struct ring_buffer_event *event)
{
	struct ring_buffer_per_cpu *cpu_buffer = buffer->buffers[smp_processor_id()];
	unsigned int nest;
	u64 ts;


	if (event->type_len == RINGBUF_TYPE_TIME_STAMP)
		return rb_event_time_stamp(event);

	nest = local_read(&cpu_buffer->committing);
	verify_event(cpu_buffer, event);
	if (WARN_ON_ONCE(!nest))
		goto fail;


	if (likely(--nest < MAX_NEST))
		return cpu_buffer->event_stamp[nest];


	WARN_ONCE(1, "nest (%d) greater than max", nest);

 fail:

	if (!rb_time_read(&cpu_buffer->write_stamp, &ts))

		ts = rb_time_stamp(cpu_buffer->buffer);

	return ts;
}
