UINT rdpgfx_write_point16(wStream* s, const RDPGFX_POINT16* point16)
{
	Stream_Write_UINT16(s, point16->x);
	Stream_Write_UINT16(s, point16->y);
	return CHANNEL_RC_OK;
}
