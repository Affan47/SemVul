static void rfx_write_message_channels(RFX_CONTEXT* context, wStream* s)
{
	Stream_Write_UINT16(s, WBT_CHANNELS);
	Stream_Write_UINT32(s, 12);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT16(s, context->width);
	Stream_Write_UINT16(s, context->height);
}
