write_to_managed (ZStream *stream)
{
	gint n;
	z_stream *zs;

	zs = stream->stream;
	if (zs->avail_out != BUFFER_SIZE) {
		n = stream->func (stream->buffer, BUFFER_SIZE - zs->avail_out, stream->gchandle);
		zs->next_out = stream->buffer;
		zs->avail_out = BUFFER_SIZE;
		if (n < 0)
			return IO_ERROR;
	}
	return 0;
}
