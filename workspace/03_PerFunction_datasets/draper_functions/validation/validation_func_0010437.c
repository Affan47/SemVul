bt_ctf_get_timestamp(const struct bt_ctf_event *ctf_event)
{
	const struct ctf_event_definition *event;

	if (!ctf_event)
		return -1ULL;

	event = ctf_event->parent;
	if (event && event->stream->has_timestamp)
		return event->stream->real_timestamp;
	else
		return -1ULL;
}
