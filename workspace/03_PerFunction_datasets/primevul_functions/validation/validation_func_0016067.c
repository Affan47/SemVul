static BOOL rdp_print_draw_gdiplus_cache_capability_set(wStream* s, UINT16 length)
{
	UINT32 drawGdiPlusSupportLevel;
	UINT32 GdipVersion;
	UINT32 drawGdiplusCacheLevel;
	WLog_INFO(TAG, "DrawGdiPlusCacheCapabilitySet (length %" PRIu16 "):", length);

	if (length < 40)
		return FALSE;

	Stream_Read_UINT32(s, drawGdiPlusSupportLevel);
	Stream_Read_UINT32(s, GdipVersion);
	Stream_Read_UINT32(s, drawGdiplusCacheLevel);
	Stream_Seek(s, 10);
	Stream_Seek(s, 8);
	Stream_Seek(s, 6);
	return TRUE;
}
