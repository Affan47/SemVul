rdp_out_general_caps(STREAM s)
{
	out_uint16_le(s, RDP_CAPSET_GENERAL);
	out_uint16_le(s, RDP_CAPLEN_GENERAL);

	out_uint16_le(s, 1);
	out_uint16_le(s, 3);
	out_uint16_le(s, 0x200);
	out_uint16(s, 0);
	out_uint16(s, 0);
	out_uint16_le(s, (g_rdp_version >= RDP_V5) ? 0x40d : 0);


	out_uint16(s, 0);
	out_uint16(s, 0);
	out_uint16(s, 0);
	out_uint16(s, 0);
}
