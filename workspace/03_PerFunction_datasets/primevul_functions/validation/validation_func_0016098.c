static BOOL rdp_write_window_list_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;

	if (!Stream_EnsureRemainingCapacity(s, 32))
		return FALSE;

	header = rdp_capability_set_start(s);
	Stream_Write_UINT32(s, settings->RemoteWndSupportLevel);
	Stream_Write_UINT8(s, settings->RemoteAppNumIconCaches);
	Stream_Write_UINT16(s,
	                    settings->RemoteAppNumIconCacheEntries);
	rdp_capability_set_finish(s, header, CAPSET_TYPE_WINDOW);
	return TRUE;
}
