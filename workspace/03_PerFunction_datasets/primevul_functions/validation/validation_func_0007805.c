static BOOL update_send_window_icon(rdpContext* context, const WINDOW_ORDER_INFO* orderInfo,
                                    const WINDOW_ICON_ORDER* iconOrder)
{
	wStream* s;
	rdpUpdate* update = context->update;
	BYTE controlFlags = ORDER_SECONDARY | (ORDER_TYPE_WINDOW << 2);
	ICON_INFO* iconInfo = iconOrder->iconInfo;
	UINT16 orderSize = update_calculate_window_icon_order(orderInfo, iconOrder);

	update_check_flush(context, orderSize);

	s = update->us;

	if (!s || !iconInfo)
		return FALSE;

	if (!Stream_EnsureRemainingCapacity(s, orderSize))
		return FALSE;


	Stream_Write_UINT8(s, controlFlags);
	Stream_Write_UINT16(s, orderSize);
	Stream_Write_UINT32(s, orderInfo->fieldFlags);
	Stream_Write_UINT32(s, orderInfo->windowId);

	Stream_Write_UINT16(s, iconInfo->cacheEntry);
	Stream_Write_UINT8(s, iconInfo->cacheId);
	Stream_Write_UINT8(s, iconInfo->bpp);
	Stream_Write_UINT16(s, iconInfo->width);
	Stream_Write_UINT16(s, iconInfo->height);

	if (iconInfo->bpp <= 8)
	{
		Stream_Write_UINT16(s, iconInfo->cbColorTable);
	}

	Stream_Write_UINT16(s, iconInfo->cbBitsMask);
	Stream_Write_UINT16(s, iconInfo->cbBitsColor);
	Stream_Write(s, iconInfo->bitsMask, iconInfo->cbBitsMask);

	if (iconInfo->bpp <= 8)
	{
		Stream_Write(s, iconInfo->colorTable, iconInfo->cbColorTable);
	}

	Stream_Write(s, iconInfo->bitsColor, iconInfo->cbBitsColor);

	update->numberOrders++;
	return TRUE;
}
