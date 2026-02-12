stream_data_align (MonoDynamicStream *stream)
{
	char buf [4] = {0};
	guint32 count = stream->index % 4;


	if (count)
		mono_image_add_stream_data (stream, buf, 4 - count);
}
