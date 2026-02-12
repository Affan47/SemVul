rb_try_to_discard(struct ring_buffer_per_cpu *cpu_buffer,
		  struct ring_buffer_event *event)
{
	unsigned long new_index, old_index;
	struct buffer_page *bpage;
	unsigned long index;
	unsigned long addr;
	u64 write_stamp;
	u64 delta;

	new_index = rb_event_index(event);
	old_index = new_index + rb_event_ts_length(event);
	addr = (unsigned long)event;
	addr &= PAGE_MASK;

	bpage = READ_ONCE(cpu_buffer->tail_page);

	delta = rb_time_delta(event);

	if (!rb_time_read(&cpu_buffer->write_stamp, &write_stamp))
		return 0;


	barrier();

	if (bpage->page == (void *)addr && rb_page_write(bpage) == old_index) {
		unsigned long write_mask =
			local_read(&bpage->write) & ~RB_WRITE_MASK;
		unsigned long event_length = rb_event_length(event);


		if (!rb_time_cmpxchg(&cpu_buffer->write_stamp,
				       write_stamp, write_stamp - delta))
			return 0;


		if (!delta)
			rb_time_set(&cpu_buffer->before_stamp, 0);


		old_index += write_mask;
		new_index += write_mask;
		index = local_cmpxchg(&bpage->write, old_index, new_index);
		if (index == old_index) {

			local_sub(event_length, &cpu_buffer->entries_bytes);
			return 1;
		}
	}


	return 0;
}
