static BOOL rdp_print_pointer_capability_set(wStream* s, UINT16 length)
{
	UINT16 colorPointerFlag;
	UINT16 colorPointerCacheSize;
	UINT16 pointerCacheSize;

	if (length < 10)
		return FALSE;

	WLog_INFO(TAG, "PointerCapabilitySet (length %" PRIu16 "):", length);
	Stream_Read_UINT16(s, colorPointerFlag);
	Stream_Read_UINT16(s, colorPointerCacheSize);
	Stream_Read_UINT16(s, pointerCacheSize);
	WLog_INFO(TAG, "\tcolorPointerFlag: 0x%04" PRIX16 "", colorPointerFlag);
	WLog_INFO(TAG, "\tcolorPointerCacheSize: 0x%04" PRIX16 "", colorPointerCacheSize);
	WLog_INFO(TAG, "\tpointerCacheSize: 0x%04" PRIX16 "", pointerCacheSize);
	return TRUE;
}
