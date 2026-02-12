UINT rdpgfx_write_rect16(wStream* s, const RECTANGLE_16* rect16)
{
	Stream_Write_UINT16(s, rect16->left);
	Stream_Write_UINT16(s, rect16->top);
	Stream_Write_UINT16(s, rect16->right);
	Stream_Write_UINT16(s, rect16->bottom);
	return CHANNEL_RC_OK;
}
