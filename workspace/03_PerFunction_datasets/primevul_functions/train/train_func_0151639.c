static BOOL rfx_write_message_region(RFX_CONTEXT* context, wStream* s, RFX_MESSAGE* message)
{
	int i;
	UINT32 blockLen;
	blockLen = 15 + (message->numRects * 8);

	if (!Stream_EnsureRemainingCapacity(s, blockLen))
		return FALSE;

	Stream_Write_UINT16(s, WBT_REGION);
	Stream_Write_UINT32(s, blockLen);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT16(s, message->numRects);

	for (i = 0; i < message->numRects; i++)
	{
		const RFX_RECT* rect = rfx_message_get_rect(message, i);

		Stream_Write_UINT16(s, rect->x);
		Stream_Write_UINT16(s, rect->y);
		Stream_Write_UINT16(s, rect->width);
		Stream_Write_UINT16(s, rect->height);
	}

	Stream_Write_UINT16(s, CBT_REGION);
	Stream_Write_UINT16(s, 1);
	return TRUE;
}
