static BOOL update_read_desktop_actively_monitored_order(wStream* s, WINDOW_ORDER_INFO* orderInfo,
                                                         MONITORED_DESKTOP_ORDER* monitored_desktop)
{
	int i;
	int size;

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_DESKTOP_ACTIVE_WND)
	{
		if (Stream_GetRemainingLength(s) < 4)
			return FALSE;

		Stream_Read_UINT32(s, monitored_desktop->activeWindowId);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_DESKTOP_ZORDER)
	{
		UINT32* newid;

		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, monitored_desktop->numWindowIds);

		if (Stream_GetRemainingLength(s) < 4 * monitored_desktop->numWindowIds)
			return FALSE;

		if (monitored_desktop->numWindowIds > 0)
		{
			size = sizeof(UINT32) * monitored_desktop->numWindowIds;
			newid = (UINT32*)realloc(monitored_desktop->windowIds, size);

			if (!newid)
			{
				free(monitored_desktop->windowIds);
				monitored_desktop->windowIds = NULL;
				return FALSE;
			}

			monitored_desktop->windowIds = newid;


			for (i = 0; i < (int)monitored_desktop->numWindowIds; i++)
			{
				Stream_Read_UINT32(s, monitored_desktop->windowIds[i]);
			}
		}
	}

	return TRUE;
}
