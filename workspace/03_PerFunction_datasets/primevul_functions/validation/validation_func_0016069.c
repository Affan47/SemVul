static BOOL rdp_read_font_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	WINPR_UNUSED(settings);
	if (length > 5)
		Stream_Seek_UINT16(s);

	if (length > 7)
		Stream_Seek_UINT16(s);

	return TRUE;
}
