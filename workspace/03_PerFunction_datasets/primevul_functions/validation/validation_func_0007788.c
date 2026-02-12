UINT rdpgfx_write_color32(wStream* s, const RDPGFX_COLOR32* color32)
{
	Stream_Write_UINT8(s, color32->B);
	Stream_Write_UINT8(s, color32->G);
	Stream_Write_UINT8(s, color32->R);
	Stream_Write_UINT8(s, color32->XA);
	return CHANNEL_RC_OK;
}
