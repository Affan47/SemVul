static BOOL rfx_write_message_frame_end(RFX_CONTEXT* context, wStream* s, RFX_MESSAGE* message)
{
	if (!Stream_EnsureRemainingCapacity(s, 8))
		return FALSE;

	Stream_Write_UINT16(s, WBT_FRAME_END);
	Stream_Write_UINT32(s, 8);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0);
	return TRUE;
}
