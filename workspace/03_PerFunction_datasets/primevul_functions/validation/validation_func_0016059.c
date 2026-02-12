static BOOL rdp_read_bitmap_cache_v2_capability_set(wStream* s, UINT16 length,
                                                    rdpSettings* settings)
{
	WINPR_UNUSED(settings);
	if (length < 40)
		return FALSE;

	Stream_Seek_UINT16(s);
	Stream_Seek_UINT8(s);
	Stream_Seek_UINT8(s);
	Stream_Seek(s, 4);
	Stream_Seek(s, 4);
	Stream_Seek(s, 4);
	Stream_Seek(s, 4);
	Stream_Seek(s, 4);
	Stream_Seek(s, 12);
	return TRUE;
}
