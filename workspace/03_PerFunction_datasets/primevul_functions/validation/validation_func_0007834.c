static BOOL update_send_notify_icon_delete(rdpContext* context, const WINDOW_ORDER_INFO* orderInfo)
{
	wStream* s;
	rdpUpdate* update = context->update;
	BYTE controlFlags = ORDER_SECONDARY | (ORDER_TYPE_WINDOW << 2);
	UINT16 orderSize = 15;
	update_check_flush(context, orderSize);

	s = update->us;

	if (!s)
		return FALSE;


	Stream_Write_UINT8(s, controlFlags);
	Stream_Write_UINT16(s, orderSize);
	Stream_Write_UINT32(s, orderInfo->fieldFlags);
	Stream_Write_UINT32(s, orderInfo->windowId);
	Stream_Write_UINT32(s, orderInfo->notifyIconId);
	update->numberOrders++;
	return TRUE;
}
