rail_vchannel_process_server_minmax_info_order(
		RAIL_SESSION* session,
		STREAM* s
		)
{
	uint32 window_id = 0;
	uint16 max_width = 0;
	uint16 max_height = 0;
	uint16 max_pos_x = 0;
	uint16 max_pos_y = 0;
	uint16 min_track_width = 0;
	uint16 min_track_height = 0;
	uint16 max_track_width = 0;
	uint16 max_track_height = 0;

	stream_read_uint32(s, window_id);
	stream_read_uint16(s, max_width);
	stream_read_uint16(s, max_height);
	stream_read_uint16(s, max_pos_x);
	stream_read_uint16(s, max_pos_y);
	stream_read_uint16(s, min_track_width);
	stream_read_uint16(s, min_track_height);
	stream_read_uint16(s, max_track_width);
	stream_read_uint16(s, max_track_height);

	rail_core_handle_server_minmax_info(session, window_id, max_width,
	    max_height, max_pos_x, max_pos_y, min_track_width, min_track_height,
	    max_track_width, max_track_height);
}
