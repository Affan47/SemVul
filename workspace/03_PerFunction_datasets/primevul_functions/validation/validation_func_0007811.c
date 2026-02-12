update_send_new_or_existing_notification_icons(rdpContext* context,
                                               const WINDOW_ORDER_INFO* orderInfo,
                                               const NOTIFY_ICON_STATE_ORDER* iconStateOrder)
{
	wStream* s;
	rdpUpdate* update = context->update;
	BYTE controlFlags = ORDER_SECONDARY | (ORDER_TYPE_WINDOW << 2);
	BOOL versionFieldPresent = FALSE;
	UINT16 orderSize =
	    update_calculate_new_or_existing_notification_icons_order(orderInfo, iconStateOrder);

	update_check_flush(context, orderSize);

	s = update->us;
	if (!s)
		return FALSE;

	if (!Stream_EnsureRemainingCapacity(s, orderSize))
		return FALSE;


	Stream_Write_UINT8(s, controlFlags);
	Stream_Write_INT16(s, orderSize);
	Stream_Write_UINT32(s, orderInfo->fieldFlags);
	Stream_Write_UINT32(s, orderInfo->windowId);
	Stream_Write_UINT32(s, orderInfo->notifyIconId);


	if ((orderInfo->fieldFlags & WINDOW_ORDER_FIELD_NOTIFY_VERSION) != 0)
	{
		versionFieldPresent = TRUE;
		Stream_Write_UINT32(s, iconStateOrder->version);
	}

	if ((orderInfo->fieldFlags & WINDOW_ORDER_FIELD_NOTIFY_TIP) != 0)
	{
		Stream_Write_UINT16(s, iconStateOrder->toolTip.length);
		Stream_Write(s, iconStateOrder->toolTip.string, iconStateOrder->toolTip.length);
	}

	if ((orderInfo->fieldFlags & WINDOW_ORDER_FIELD_NOTIFY_INFO_TIP) != 0)
	{
		NOTIFY_ICON_INFOTIP infoTip = iconStateOrder->infoTip;


		if (versionFieldPresent && iconStateOrder->version == 0)
			return FALSE;

		Stream_Write_UINT32(s, infoTip.timeout);
		Stream_Write_UINT32(s, infoTip.flags);
		Stream_Write_UINT16(s, infoTip.text.length);
		Stream_Write(s, infoTip.text.string, infoTip.text.length);
		Stream_Write_UINT16(s, infoTip.title.length);
		Stream_Write(s, infoTip.title.string, infoTip.title.length);
	}

	if ((orderInfo->fieldFlags & WINDOW_ORDER_FIELD_NOTIFY_STATE) != 0)
	{

		if (versionFieldPresent && iconStateOrder->version == 0)
			return FALSE;

		Stream_Write_UINT32(s, iconStateOrder->state);
	}

	if ((orderInfo->fieldFlags & WINDOW_ORDER_ICON) != 0)
	{
		ICON_INFO iconInfo = iconStateOrder->icon;
		Stream_Write_UINT16(s, iconInfo.cacheEntry);
		Stream_Write_UINT8(s, iconInfo.cacheId);
		Stream_Write_UINT8(s, iconInfo.bpp);
		Stream_Write_UINT16(s, iconInfo.width);
		Stream_Write_UINT16(s, iconInfo.height);

		if (iconInfo.bpp <= 8)
		{
			Stream_Write_UINT16(s, iconInfo.cbColorTable);
		}

		Stream_Write_UINT16(s, iconInfo.cbBitsMask);
		Stream_Write_UINT16(s, iconInfo.cbBitsColor);
		Stream_Write(s, iconInfo.bitsMask, iconInfo.cbBitsMask);
		orderSize += iconInfo.cbBitsMask;

		if (iconInfo.bpp <= 8)
		{
			Stream_Write(s, iconInfo.colorTable, iconInfo.cbColorTable);
		}

		Stream_Write(s, iconInfo.bitsColor, iconInfo.cbBitsColor);
	}
	else if ((orderInfo->fieldFlags & WINDOW_ORDER_CACHED_ICON) != 0)
	{
		CACHED_ICON_INFO cachedIcon = iconStateOrder->cachedIcon;
		Stream_Write_UINT16(s, cachedIcon.cacheEntry);
		Stream_Write_UINT8(s, cachedIcon.cacheId);
	}

	update->numberOrders++;
	return TRUE;
}
