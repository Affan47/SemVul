static BOOL rfx_write_message_tileset(RFX_CONTEXT* context, wStream* s, RFX_MESSAGE* message)
{
	int i;
	RFX_TILE* tile;
	UINT32 blockLen;
	UINT32* quantVals;
	blockLen = 22 + (message->numQuant * 5) + message->tilesDataSize;

	if (!Stream_EnsureRemainingCapacity(s, blockLen))
		return FALSE;

	Stream_Write_UINT16(s, WBT_EXTENSION);
	Stream_Write_UINT32(s, blockLen);
	Stream_Write_UINT8(s, 1);
	Stream_Write_UINT8(s, 0);
	Stream_Write_UINT16(s, CBT_TILESET);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, context->properties);
	Stream_Write_UINT8(s, message->numQuant);
	Stream_Write_UINT8(s, 0x40);
	Stream_Write_UINT16(s, message->numTiles);
	Stream_Write_UINT32(s, message->tilesDataSize);
	quantVals = message->quantVals;

	for (i = 0; i < message->numQuant * 5; i++)
	{
		Stream_Write_UINT8(s, quantVals[0] + (quantVals[1] << 4));
		quantVals += 2;
	}

	for (i = 0; i < message->numTiles; i++)
	{
		if (!(tile = message->tiles[i]))
			return FALSE;

		if (!rfx_write_tile(context, s, tile))
			return FALSE;
	}

#ifdef WITH_DEBUG_RFX
	WLog_Print(context->priv->log, WLOG_DEBUG,
	           "numQuant: %" PRIu16 " numTiles: %" PRIu16 " tilesDataSize: %" PRIu32 "",
	           message->numQuant, message->numTiles, message->tilesDataSize);
#endif
	return TRUE;
}
