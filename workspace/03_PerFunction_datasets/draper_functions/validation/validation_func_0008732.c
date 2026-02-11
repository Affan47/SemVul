git_stream_write(
	git_smart_subtransport_stream *stream,
	const char *buffer,
	size_t len)
{
	int error;
	git_stream *s = (git_stream *)stream;

	if (!s->sent_command && (error = send_command(s)) < 0)
		return error;

	return gitno_send(&s->socket, buffer, len, 0);
}
