static BOOL rfx_write_tile(RFX_CONTEXT* context, wStream* s, RFX_TILE* tile)
{
	UINT32 blockLen;
	blockLen = rfx_tile_length(tile);

	if (!Stream_EnsureRemainingCapacity(s, blockLen))
		return FALSE;

	Stream_Write_UINT16(s, CBT_TILE);
	Stream_Write_UINT32(s, blockLen);
	Stream_Write_UINT8(s, tile->quantIdxY);
	Stream_Write_UINT8(s, tile->quantIdxCb);
	Stream_Write_UINT8(s, tile->quantIdxCr);
	Stream_Write_UINT16(s, tile->xIdx);
	Stream_Write_UINT16(s, tile->yIdx);
	Stream_Write_UINT16(s, tile->YLen);
	Stream_Write_UINT16(s, tile->CbLen);
	Stream_Write_UINT16(s, tile->CrLen);
	Stream_Write(s, tile->YData, tile->YLen);
	Stream_Write(s, tile->CbData, tile->CbLen);
	Stream_Write(s, tile->CrData, tile->CrLen);
	return TRUE;
}
