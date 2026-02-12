static void rb_inc_iter(struct ring_buffer_iter *iter)
{
	struct ring_buffer_per_cpu *cpu_buffer = iter->cpu_buffer;


	if (iter->head_page == cpu_buffer->reader_page)
		iter->head_page = rb_set_head_page(cpu_buffer);
	else
		rb_inc_page(&iter->head_page);

	iter->page_stamp = iter->read_stamp = iter->head_page->page->time_stamp;
	iter->head = 0;
	iter->next_event = 0;
}
