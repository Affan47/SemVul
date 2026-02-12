static BOOL rdp_read_bitmap_cache_host_support_capability_set(wStream* s, UINT16 length,
                                                              rdpSettings* settings)
{
	BYTE cacheVersion;

	if (length < 8)
		return FALSE;

	Stream_Read_UINT8(s, cacheVersion);
	Stream_Seek_UINT8(s);
	Stream_Seek_UINT16(s);

	if (cacheVersion & BITMAP_CACHE_V2)
		settings->BitmapCachePersistEnabled = TRUE;

	return TRUE;
}
