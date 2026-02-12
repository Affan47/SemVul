static BOOL rdp_read_offscreen_bitmap_cache_capability_set(wStream* s, UINT16 length,
                                                           rdpSettings* settings)
{
	UINT32 offscreenSupportLevel;

	if (length < 12)
		return FALSE;

	Stream_Read_UINT32(s, offscreenSupportLevel);
	Stream_Read_UINT16(s, settings->OffscreenCacheSize);
	Stream_Read_UINT16(s, settings->OffscreenCacheEntries);

	if (offscreenSupportLevel & TRUE)
		settings->OffscreenSupportLevel = TRUE;

	return TRUE;
}
