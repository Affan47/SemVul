static BOOL rfx_write_message_frame_begin(RFX_CONTEXT* context, wStream* s, RFX_MESSAGE* message)
{
	if (!Stream_EnsureRemainingCapacity(s, 14))
		return FALSE;

	Stream_Write_UINT16(s, WBT_FRAME_BEGIN);
	Stream_Write_UINT32(s, 14);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT32(s, message->frameIdx);
	Stream_Write_UINT16(s, 1);
	return TRUE;
}
