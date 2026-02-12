UINT rdpgfx_write_header(wStream* s, const RDPGFX_HEADER* header)
{
	Stream_Write_UINT16(s, header->cmdId);
	Stream_Write_UINT16(s, header->flags);
	Stream_Write_UINT32(s, header->pduLength);
	return CHANNEL_RC_OK;
}
