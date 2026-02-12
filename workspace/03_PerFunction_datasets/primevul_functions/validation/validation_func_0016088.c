static BOOL rdp_read_window_list_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	if (length < 11)
		return FALSE;

	Stream_Read_UINT32(s, settings->RemoteWndSupportLevel);
	Stream_Read_UINT8(s, settings->RemoteAppNumIconCaches);
	Stream_Read_UINT16(s,
	                   settings->RemoteAppNumIconCacheEntries);
	return TRUE;
}
