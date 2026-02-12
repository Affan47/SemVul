static void rfx_write_message_sync(RFX_CONTEXT* context, wStream* s)
{
	Stream_Write_UINT16(s, WBT_SYNC);
	Stream_Write_UINT32(s, 12);
	Stream_Write_UINT32(s, WF_MAGIC);
	Stream_Write_UINT16(s, WF_VERSION_1_0);
}
