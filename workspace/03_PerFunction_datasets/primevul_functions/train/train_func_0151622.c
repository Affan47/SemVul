static BOOL rfx_process_message_region(RFX_CONTEXT* context, RFX_MESSAGE* message, wStream* s,
                                       UINT16* pExpectedBlockType)
{
	int i;
	UINT16 regionType;
	UINT16 numTileSets;
	RFX_RECT* tmpRects;

	if (*pExpectedBlockType != WBT_REGION)
	{
		WLog_ERR(TAG, "%s: message unexpected wants WBT_REGION", __FUNCTION__);
		return FALSE;
	}

	*pExpectedBlockType = WBT_EXTENSION;

	if (Stream_GetRemainingLength(s) < 3)
	{
		WLog_ERR(TAG, "%s: packet too small (regionFlags/numRects)", __FUNCTION__);
		return FALSE;
	}

	Stream_Seek_UINT8(s);
	Stream_Read_UINT16(s, message->numRects);

	if (message->numRects < 1)
	{


		tmpRects = realloc(message->rects, sizeof(RFX_RECT));
		if (!tmpRects)
			return FALSE;

		message->numRects = 1;
		message->rects = tmpRects;
		message->rects->x = 0;
		message->rects->y = 0;
		message->rects->width = context->width;
		message->rects->height = context->height;
		return TRUE;
	}

	if (Stream_GetRemainingLength(s) < (size_t)(8 * message->numRects))
	{
		WLog_ERR(TAG, "%s: packet too small for num_rects=%" PRIu16 "", __FUNCTION__,
		         message->numRects);
		return FALSE;
	}

	tmpRects = realloc(message->rects, message->numRects * sizeof(RFX_RECT));
	if (!tmpRects)
		return FALSE;
	message->rects = tmpRects;


	for (i = 0; i < message->numRects; i++)
	{
		RFX_RECT* rect = rfx_message_get_rect(message, i);

		Stream_Read_UINT16(s, rect->x);
		Stream_Read_UINT16(s, rect->y);
		Stream_Read_UINT16(s, rect->width);
		Stream_Read_UINT16(s, rect->height);
		WLog_Print(context->priv->log, WLOG_DEBUG,
		           "rect %d (x,y=%" PRIu16 ",%" PRIu16 " w,h=%" PRIu16 " %" PRIu16 ").", i, rect->x,
		           rect->y, rect->width, rect->height);
	}

	if (Stream_GetRemainingLength(s) < 4)
	{
		WLog_ERR(TAG, "%s: packet too small (regionType/numTileSets)", __FUNCTION__);
		return FALSE;
	}

	Stream_Read_UINT16(s, regionType);
	Stream_Read_UINT16(s, numTileSets);

	if (regionType != CBT_REGION)
	{
		WLog_ERR(TAG, "%s: invalid region type 0x%04" PRIX16 "", __FUNCTION__, regionType);
		return TRUE;
	}

	if (numTileSets != 0x0001)
	{
		WLog_ERR(TAG, "%s: invalid number of tilesets (%" PRIu16 ")", __FUNCTION__, numTileSets);
		return FALSE;
	}

	return TRUE;
}
