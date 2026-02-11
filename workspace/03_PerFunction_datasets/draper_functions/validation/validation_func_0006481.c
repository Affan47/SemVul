read_buffer(STREAM *stream, void **addr, int *len)
{
	int l = stream->common.buffer_len - stream->common.buffer_pos;
	if (l > *len)
		l = *len;
	if (l > 0)
	{
		memcpy(*addr, stream->common.buffer + stream->common.buffer_pos, l);
		*addr = (char *)*addr + l;
		*len -= l;
		STREAM_eff_read += l;
		stream->common.buffer_pos += l;
	}
}
