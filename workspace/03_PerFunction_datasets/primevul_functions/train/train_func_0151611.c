static void rfx_write_message_codec_versions(RFX_CONTEXT* context, wStream* s)
{
	Stream_Write_UINT16(s, WBT_CODEC_VERSIONS);
	Stream_Write_UINT32(s, 10);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT16(s, WF_VERSION_1_0);
}
