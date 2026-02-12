int bgp_packet_set_marker(struct stream *s, uint8_t type)
{
	int i;


	for (i = 0; i < BGP_MARKER_SIZE; i++)
		stream_putc(s, 0xff);


	stream_putw(s, 0);


	stream_putc(s, type);


	return stream_get_endp(s);
}
