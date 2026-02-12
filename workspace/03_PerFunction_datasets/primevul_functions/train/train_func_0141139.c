rdp_out_bitmap_caps(STREAM s)
{
	out_uint16_le(s, RDP_CAPSET_BITMAP);
	out_uint16_le(s, RDP_CAPLEN_BITMAP);

	out_uint16_le(s, g_server_depth);
	out_uint16_le(s, 1);
	out_uint16_le(s, 1);
	out_uint16_le(s, 1);
	out_uint16_le(s, 800);
	out_uint16_le(s, 600);
	out_uint16(s, 0);
	out_uint16(s, 1);
	out_uint16_le(s, g_bitmap_compression ? 1 : 0);
	out_uint16(s, 0);
	out_uint16_le(s, 1);
	out_uint16(s, 0);
}
