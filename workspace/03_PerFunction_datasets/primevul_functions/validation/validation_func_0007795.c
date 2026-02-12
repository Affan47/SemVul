static BOOL update_send_window_cached_icon(rdpContext* context, const WINDOW_ORDER_INFO* orderInfo,
                                           const WINDOW_CACHED_ICON_ORDER* cachedIconOrder)
{
	wStream* s;
	rdpUpdate* update = context->update;
	BYTE controlFlags = ORDER_SECONDARY | (ORDER_TYPE_WINDOW << 2);
	UINT16 orderSize = 14;
	CACHED_ICON_INFO cachedIcon = cachedIconOrder->cachedIcon;

	update_check_flush(context, orderSize);

	s = update->us;
	if (!s)
		return FALSE;

	if (!Stream_EnsureRemainingCapacity(s, orderSize))
		return FALSE;


	Stream_Write_UINT8(s, controlFlags);
	Stream_Write_UINT16(s, orderSize);
	Stream_Write_UINT32(s, orderInfo->fieldFlags);
	Stream_Write_UINT32(s, orderInfo->windowId);

	Stream_Write_UINT16(s, cachedIcon.cacheEntry);
	Stream_Write_UINT8(s, cachedIcon.cacheId);
	update->numberOrders++;
	return TRUE;
}
