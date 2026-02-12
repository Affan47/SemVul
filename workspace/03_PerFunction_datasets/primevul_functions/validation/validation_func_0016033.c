static BOOL rdp_write_pointer_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;
	UINT16 colorPointerFlag;

	if (!Stream_EnsureRemainingCapacity(s, 32))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;
	if (settings->PointerCacheSize > UINT16_MAX)
		return FALSE;

	colorPointerFlag = (settings->ColorPointerFlag) ? 1 : 0;
	Stream_Write_UINT16(s, colorPointerFlag);
	Stream_Write_UINT16(s,
	                    (UINT16)settings->PointerCacheSize);

	if (settings->LargePointerFlag)
	{
		Stream_Write_UINT16(s, (UINT16)settings->PointerCacheSize);
	}

	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_POINTER);
	return TRUE;
}
