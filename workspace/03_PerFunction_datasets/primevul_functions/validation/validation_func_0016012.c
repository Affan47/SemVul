static BOOL rdp_write_draw_gdiplus_cache_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;
	UINT32 drawGDIPlusSupportLevel;
	UINT32 drawGdiplusCacheLevel;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	header = rdp_capability_set_start(s);
	drawGDIPlusSupportLevel =
	    (settings->DrawGdiPlusEnabled) ? DRAW_GDIPLUS_SUPPORTED : DRAW_GDIPLUS_DEFAULT;
	drawGdiplusCacheLevel = (settings->DrawGdiPlusEnabled) ? DRAW_GDIPLUS_CACHE_LEVEL_ONE
	                                                       : DRAW_GDIPLUS_CACHE_LEVEL_DEFAULT;
	Stream_Write_UINT32(s, drawGDIPlusSupportLevel);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, drawGdiplusCacheLevel);
	rdp_write_gdiplus_cache_entries(s, 10, 5, 5, 10, 2);
	rdp_write_gdiplus_cache_chunk_size(s, 512, 2048, 1024, 64);
	rdp_write_gdiplus_image_cache_properties(s, 4096, 256,
	                                         128);
	rdp_capability_set_finish(s, header, CAPSET_TYPE_DRAW_GDI_PLUS);
	return TRUE;
}
