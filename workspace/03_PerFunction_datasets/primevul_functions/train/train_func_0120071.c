static BOOL update_read_icon_info(wStream* s, ICON_INFO* iconInfo)
{
	BYTE* newBitMask;

	if (Stream_GetRemainingLength(s) < 8)
		return FALSE;

	Stream_Read_UINT16(s, iconInfo->cacheEntry);
	Stream_Read_UINT8(s, iconInfo->cacheId);
	Stream_Read_UINT8(s, iconInfo->bpp);

	if ((iconInfo->bpp < 1) || (iconInfo->bpp > 32))
	{
		WLog_ERR(TAG, "invalid bpp value %" PRIu32 "", iconInfo->bpp);
		return FALSE;
	}

	Stream_Read_UINT16(s, iconInfo->width);
	Stream_Read_UINT16(s, iconInfo->height);


	switch (iconInfo->bpp)
	{
		case 1:
		case 4:
		case 8:
			if (Stream_GetRemainingLength(s) < 2)
				return FALSE;

			Stream_Read_UINT16(s, iconInfo->cbColorTable);
			break;

		default:
			iconInfo->cbColorTable = 0;
			break;
	}

	if (Stream_GetRemainingLength(s) < 4)
		return FALSE;

	Stream_Read_UINT16(s, iconInfo->cbBitsMask);
	Stream_Read_UINT16(s, iconInfo->cbBitsColor);


	newBitMask = (BYTE*)realloc(iconInfo->bitsMask, iconInfo->cbBitsMask);

	if (!newBitMask)
	{
		free(iconInfo->bitsMask);
		iconInfo->bitsMask = NULL;
		return FALSE;
	}

	iconInfo->bitsMask = newBitMask;
	if (Stream_GetRemainingLength(s) < iconInfo->cbBitsMask)
		return FALSE;
	Stream_Read(s, iconInfo->bitsMask, iconInfo->cbBitsMask);


	if (iconInfo->colorTable == NULL)
	{
		if (iconInfo->cbColorTable)
		{
			iconInfo->colorTable = (BYTE*)malloc(iconInfo->cbColorTable);

			if (!iconInfo->colorTable)
				return FALSE;
		}
	}
	else if (iconInfo->cbColorTable)
	{
		BYTE* new_tab;
		new_tab = (BYTE*)realloc(iconInfo->colorTable, iconInfo->cbColorTable);

		if (!new_tab)
		{
			free(iconInfo->colorTable);
			iconInfo->colorTable = NULL;
			return FALSE;
		}

		iconInfo->colorTable = new_tab;
	}
	else
	{
		free(iconInfo->colorTable);
		iconInfo->colorTable = NULL;
	}

	if (iconInfo->colorTable)
	{
		if (Stream_GetRemainingLength(s) < iconInfo->cbColorTable)
			return FALSE;
		Stream_Read(s, iconInfo->colorTable, iconInfo->cbColorTable);
	}


	newBitMask = (BYTE*)realloc(iconInfo->bitsColor, iconInfo->cbBitsColor);

	if (!newBitMask)
	{
		free(iconInfo->bitsColor);
		iconInfo->bitsColor = NULL;
		return FALSE;
	}

	iconInfo->bitsColor = newBitMask;
	if (Stream_GetRemainingLength(s) < iconInfo->cbBitsColor)
		return FALSE;
	Stream_Read(s, iconInfo->bitsColor, iconInfo->cbBitsColor);
	return TRUE;
}
