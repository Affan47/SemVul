static void rfx_write_message_context(RFX_CONTEXT* context, wStream* s)
{
	UINT16 properties;
	Stream_Write_UINT16(s, WBT_CONTEXT);
	Stream_Write_UINT32(s, 13);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0xFF);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT16(s, CT_TILE_64x64);

	properties = context->flags;
	properties |= (COL_CONV_ICT << 3);
	properties |= (CLW_XFORM_DWT_53_A << 5);
	properties |= ((context->mode == RLGR1 ? CLW_ENTROPY_RLGR1 : CLW_ENTROPY_RLGR3) << 9);
	properties |= (SCALAR_QUANTIZATION << 13);
	Stream_Write_UINT16(s, properties);
	rfx_update_context_properties(context);
}
