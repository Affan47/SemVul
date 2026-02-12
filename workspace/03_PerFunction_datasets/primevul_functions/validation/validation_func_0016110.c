static BOOL rdp_read_bitmap_cache_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	WINPR_UNUSED(settings);
	if (length < 40)
		return FALSE;

	Stream_Seek_UINT32(s);
	Stream_Seek_UINT32(s);
	Stream_Seek_UINT32(s);
	Stream_Seek_UINT32(s);
	Stream_Seek_UINT32(s);
	Stream_Seek_UINT32(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	return TRUE;
}
