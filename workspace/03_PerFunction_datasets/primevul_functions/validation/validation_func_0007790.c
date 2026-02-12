UINT rdpgfx_read_color32(wStream* s, RDPGFX_COLOR32* color32)
{
	if (Stream_GetRemainingLength(s) < 4)
	{
		WLog_ERR(TAG, "not enough data!");
		return ERROR_INVALID_DATA;
	}

	Stream_Read_UINT8(s, color32->B);
	Stream_Read_UINT8(s, color32->G);
	Stream_Read_UINT8(s, color32->R);
	Stream_Read_UINT8(s, color32->XA);
	return CHANNEL_RC_OK;
}
