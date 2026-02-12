static BOOL update_send_monitored_desktop(rdpContext* context, const WINDOW_ORDER_INFO* orderInfo,
                                          const MONITORED_DESKTOP_ORDER* monitoredDesktop)
{
	UINT32 i;
	wStream* s;
	rdpUpdate* update = context->update;
	BYTE controlFlags = ORDER_SECONDARY | (ORDER_TYPE_WINDOW << 2);
	UINT16 orderSize = update_calculate_monitored_desktop(orderInfo, monitoredDesktop);
	update_check_flush(context, orderSize);

	s = update->us;

	if (!s)
		return FALSE;

	Stream_Write_UINT8(s, controlFlags);
	Stream_Write_UINT16(s, orderSize);
	Stream_Write_UINT32(s, orderInfo->fieldFlags);

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_DESKTOP_ACTIVE_WND)
	{
		Stream_Write_UINT32(s, monitoredDesktop->activeWindowId);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_DESKTOP_ZORDER)
	{
		Stream_Write_UINT8(s, monitoredDesktop->numWindowIds);


		for (i = 0; i < monitoredDesktop->numWindowIds; i++)
		{
			Stream_Write_UINT32(s, monitoredDesktop->windowIds[i]);
		}
	}

	update->numberOrders++;
	return TRUE;
}
