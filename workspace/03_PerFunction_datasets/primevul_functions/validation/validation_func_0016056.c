static BOOL rdp_write_bitmap_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;
	BYTE drawingFlags = 0;
	UINT16 preferredBitsPerPixel;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;
	if (settings->DrawAllowSkipAlpha)
		drawingFlags |= DRAW_ALLOW_SKIP_ALPHA;

	if (settings->DrawAllowDynamicColorFidelity)
		drawingFlags |= DRAW_ALLOW_DYNAMIC_COLOR_FIDELITY;

	if (settings->DrawAllowColorSubsampling)
		drawingFlags |= DRAW_ALLOW_COLOR_SUBSAMPLING;


	if ((settings->ColorDepth > UINT16_MAX) || (settings->DesktopWidth > UINT16_MAX) ||
	    (settings->DesktopHeight > UINT16_MAX) || (settings->DesktopResize > UINT16_MAX))
		return FALSE;

	if (settings->RdpVersion >= RDP_VERSION_5_PLUS)
		preferredBitsPerPixel = (UINT16)settings->ColorDepth;
	else
		preferredBitsPerPixel = 8;

	Stream_Write_UINT16(s, preferredBitsPerPixel);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT16(s, (UINT16)settings->DesktopWidth);
	Stream_Write_UINT16(s, (UINT16)settings->DesktopHeight);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, (UINT16)settings->DesktopResize);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT8(s, drawingFlags);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT16(s, 0);
	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_BITMAP);
	return TRUE;
}
