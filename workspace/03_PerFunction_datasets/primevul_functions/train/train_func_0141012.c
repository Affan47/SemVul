rdpdr_send_client_capability_response(void)
{

	STREAM s;
	s = channel_init(rdpdr_channel, 0x50);
	out_uint16_le(s, RDPDR_CTYP_CORE);
	out_uint16_le(s, PAKID_CORE_CLIENT_CAPABILITY);
	out_uint32_le(s, 5);
	out_uint16_le(s, 1);
	out_uint16_le(s, 0x28);
	out_uint32_le(s, 1);
	out_uint32_le(s, 2);
	out_uint16_le(s, 2);
	out_uint16_le(s, 5);
	out_uint16_le(s, 1);
	out_uint16_le(s, 5);
	out_uint16_le(s, 0xFFFF);
	out_uint16_le(s, 0);
	out_uint32_le(s, 0);
	out_uint32_le(s, 3);
	out_uint32_le(s, 0);
	out_uint32_le(s, 0);
	out_uint16_le(s, 2);
	out_uint16_le(s, 8);
	out_uint32_le(s, 1);
	out_uint16_le(s, 3);
	out_uint16_le(s, 8);
	out_uint32_le(s, 1);
	out_uint16_le(s, 4);
	out_uint16_le(s, 8);
	out_uint32_le(s, 1);
	out_uint16_le(s, 5);
	out_uint16_le(s, 8);
	out_uint32_le(s, 1);

	s_mark_end(s);
	channel_send(s, rdpdr_channel);
}
