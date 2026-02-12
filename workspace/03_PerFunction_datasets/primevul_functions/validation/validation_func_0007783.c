UINT rdpgfx_read_header(wStream* s, RDPGFX_HEADER* header)
{
	if (Stream_GetRemainingLength(s) < 8)
	{
		WLog_ERR(TAG, "calloc failed!");
		return CHANNEL_RC_NO_MEMORY;
	}

	Stream_Read_UINT16(s, header->cmdId);
	Stream_Read_UINT16(s, header->flags);
	Stream_Read_UINT32(s, header->pduLength);
	return CHANNEL_RC_OK;
}
