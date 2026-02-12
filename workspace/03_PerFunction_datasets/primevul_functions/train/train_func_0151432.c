static bool rb_per_cpu_empty(struct ring_buffer_per_cpu *cpu_buffer)
{
	struct buffer_page *reader = cpu_buffer->reader_page;
	struct buffer_page *head = rb_set_head_page(cpu_buffer);
	struct buffer_page *commit = cpu_buffer->commit_page;


	if (unlikely(!head))
		return true;


	if (reader->read != rb_page_commit(reader))
		return false;


	if (commit == reader)
		return true;


	if (commit != head)
		return false;


	return rb_page_commit(commit) == 0;
}
