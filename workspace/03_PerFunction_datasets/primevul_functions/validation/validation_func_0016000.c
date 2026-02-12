static BOOL rdp_write_order_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;
	UINT16 orderFlags;
	UINT16 orderSupportExFlags;
	UINT16 textANSICodePage = 0;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;

	if (!settings->ServerMode)
		textANSICodePage = CP_UTF8;

	orderSupportExFlags = 0;
	orderFlags = NEGOTIATE_ORDER_SUPPORT | ZERO_BOUNDS_DELTA_SUPPORT | COLOR_INDEX_SUPPORT;

	if (settings->BitmapCacheV3Enabled)
	{
		orderSupportExFlags |= CACHE_BITMAP_V3_SUPPORT;
		orderFlags |= ORDER_FLAGS_EXTRA_SUPPORT;
	}

	if (settings->FrameMarkerCommandEnabled)
	{
		orderSupportExFlags |= ALTSEC_FRAME_MARKER_SUPPORT;
		orderFlags |= ORDER_FLAGS_EXTRA_SUPPORT;
	}

	Stream_Zero(s, 16);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT16(s, 20);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, 1);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, orderFlags);
	Stream_Write(s, settings->OrderSupport, 32);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, orderSupportExFlags);
	Stream_Write_UINT32(s, 0);
	Stream_Write_UINT32(s, 230400);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, textANSICodePage);
	Stream_Write_UINT16(s, 0);
	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_ORDER);
	return TRUE;
}
