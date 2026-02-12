static BOOL rdp_read_control_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	WINPR_UNUSED(settings);
	if (length < 12)
		return FALSE;

	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	return TRUE;
}
