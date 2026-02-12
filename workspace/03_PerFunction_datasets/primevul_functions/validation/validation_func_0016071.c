static BOOL rdp_write_bitmap_cache_capability_set(wStream* s, const rdpSettings* settings)
{
	UINT32 bpp;
	size_t header;
	UINT32 size;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;
	bpp = (settings->ColorDepth + 7) / 8;
	if (bpp > UINT16_MAX)
		return FALSE;
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, 0);
	size = bpp * 256;
	if (size > UINT16_MAX)
		return FALSE;
	Stream_Write_UINT16(s, 200);
	Stream_Write_UINT16(s, (UINT16)size);
	size = bpp * 1024;
	if (size > UINT16_MAX)
		return FALSE;
	Stream_Write_UINT16(s, 600);
	Stream_Write_UINT16(s, (UINT16)size);
	size = bpp * 4096;
	if (size > UINT16_MAX)
		return FALSE;
	Stream_Write_UINT16(s, 1000);
	Stream_Write_UINT16(s, (UINT16)size);
	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_BITMAP_CACHE);
	return TRUE;
}
