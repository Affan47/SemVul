UINT rdpgfx_read_rect16(wStream* s, RECTANGLE_16* rect16)
{
	if (Stream_GetRemainingLength(s) < 8)
	{
		WLog_ERR(TAG, "not enough data!");
		return ERROR_INVALID_DATA;
	}

	Stream_Read_UINT16(s, rect16->left);
	Stream_Read_UINT16(s, rect16->top);
	Stream_Read_UINT16(s, rect16->right);
	Stream_Read_UINT16(s, rect16->bottom);
	if (rect16->left >= rect16->right)
		return ERROR_INVALID_DATA;
	if (rect16->top >= rect16->bottom)
		return ERROR_INVALID_DATA;
	return CHANNEL_RC_OK;
}
