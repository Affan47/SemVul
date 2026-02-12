static BOOL license_write_preamble(wStream* s, BYTE bMsgType, BYTE flags, UINT16 wMsgSize)
{
	if (!Stream_EnsureRemainingCapacity(s, 4))
		return FALSE;


	Stream_Write_UINT8(s, bMsgType);
	Stream_Write_UINT8(s, flags);
	Stream_Write_UINT16(s, wMsgSize);
	return TRUE;
}
