wake_up_event_readers(struct service_processor *sp)
{
	struct event_reader *reader;

	list_for_each_entry(reader, &sp->event_buffer->readers, node)
                wake_up_interruptible(&reader->wait);
}
