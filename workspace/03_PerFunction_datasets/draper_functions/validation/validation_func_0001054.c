bts_config_buffer(struct bts_buffer *buf)
{
	int cpu = raw_smp_processor_id();
	struct debug_store *ds = per_cpu(cpu_hw_events, cpu).ds;
	struct bts_phys *phys = &buf->buf[buf->cur_buf];
	unsigned long index, thresh = 0, end = phys->size;
	struct page *page = phys->page;

	index = local_read(&buf->head);

	if (!buf->snapshot) {
		if (buf->end < phys->offset + buf_size(page))
			end = buf->end - phys->offset - phys->displacement;

		index -= phys->offset + phys->displacement;

		if (end - index > BTS_SAFETY_MARGIN)
			thresh = end - BTS_SAFETY_MARGIN;
		else if (end - index > BTS_RECORD_SIZE)
			thresh = end - BTS_RECORD_SIZE;
		else
			thresh = end;
	}

	ds->bts_buffer_base = (u64)(long)page_address(page) + phys->displacement;
	ds->bts_index = ds->bts_buffer_base + index;
	ds->bts_absolute_maximum = ds->bts_buffer_base + end;
	ds->bts_interrupt_threshold = !buf->snapshot
		? ds->bts_buffer_base + thresh
		: ds->bts_absolute_maximum + BTS_RECORD_SIZE;
}
