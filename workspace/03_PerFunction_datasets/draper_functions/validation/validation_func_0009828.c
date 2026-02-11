soup_content_sniffer_stream_can_poll (GPollableInputStream *pollable)
{
	GInputStream *base_stream = G_FILTER_INPUT_STREAM (pollable)->base_stream;

	return G_IS_POLLABLE_INPUT_STREAM (base_stream) &&
		g_pollable_input_stream_can_poll (G_POLLABLE_INPUT_STREAM (base_stream));
}
