static BOOL update_read_window_state_order(wStream* s, WINDOW_ORDER_INFO* orderInfo,
                                           WINDOW_STATE_ORDER* windowState)
{
	UINT32 i;
	size_t size;
	RECTANGLE_16* newRect;

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_OWNER)
	{
		if (Stream_GetRemainingLength(s) < 4)
			return FALSE;

		Stream_Read_UINT32(s, windowState->ownerWindowId);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_STYLE)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_UINT32(s, windowState->style);
		Stream_Read_UINT32(s, windowState->extendedStyle);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_SHOW)
	{
		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, windowState->showState);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_TITLE)
	{
		if (!rail_read_unicode_string(s, &windowState->titleInfo))
			return FALSE;
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_OFFSET)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_INT32(s, windowState->clientOffsetX);
		Stream_Read_INT32(s, windowState->clientOffsetY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_CLIENT_AREA_SIZE)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_UINT32(s, windowState->clientAreaWidth);
		Stream_Read_UINT32(s, windowState->clientAreaHeight);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_RESIZE_MARGIN_X)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_UINT32(s, windowState->resizeMarginLeft);
		Stream_Read_UINT32(s, windowState->resizeMarginRight);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_RESIZE_MARGIN_Y)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_UINT32(s, windowState->resizeMarginTop);
		Stream_Read_UINT32(s, windowState->resizeMarginBottom);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_RP_CONTENT)
	{
		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, windowState->RPContent);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_ROOT_PARENT)
	{
		if (Stream_GetRemainingLength(s) < 4)
			return FALSE;

		Stream_Read_UINT32(s, windowState->rootParentHandle);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_OFFSET)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_INT32(s, windowState->windowOffsetX);
		Stream_Read_INT32(s, windowState->windowOffsetY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_CLIENT_DELTA)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_INT32(s, windowState->windowClientDeltaX);
		Stream_Read_INT32(s, windowState->windowClientDeltaY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_SIZE)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_UINT32(s, windowState->windowWidth);
		Stream_Read_UINT32(s, windowState->windowHeight);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_WND_RECTS)
	{
		if (Stream_GetRemainingLength(s) < 2)
			return FALSE;

		Stream_Read_UINT16(s, windowState->numWindowRects);

		if (windowState->numWindowRects == 0)
		{
			return TRUE;
		}

		size = sizeof(RECTANGLE_16) * windowState->numWindowRects;
		newRect = (RECTANGLE_16*)realloc(windowState->windowRects, size);

		if (!newRect)
		{
			free(windowState->windowRects);
			windowState->windowRects = NULL;
			return FALSE;
		}

		windowState->windowRects = newRect;

		if (Stream_GetRemainingLength(s) < 8 * windowState->numWindowRects)
			return FALSE;


		for (i = 0; i < windowState->numWindowRects; i++)
		{
			Stream_Read_UINT16(s, windowState->windowRects[i].left);
			Stream_Read_UINT16(s, windowState->windowRects[i].top);
			Stream_Read_UINT16(s, windowState->windowRects[i].right);
			Stream_Read_UINT16(s, windowState->windowRects[i].bottom);
		}
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_VIS_OFFSET)
	{
		if (Stream_GetRemainingLength(s) < 8)
			return FALSE;

		Stream_Read_UINT32(s, windowState->visibleOffsetX);
		Stream_Read_UINT32(s, windowState->visibleOffsetY);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_VISIBILITY)
	{
		if (Stream_GetRemainingLength(s) < 2)
			return FALSE;

		Stream_Read_UINT16(s, windowState->numVisibilityRects);

		if (windowState->numVisibilityRects != 0)
		{
			size = sizeof(RECTANGLE_16) * windowState->numVisibilityRects;
			newRect = (RECTANGLE_16*)realloc(windowState->visibilityRects, size);

			if (!newRect)
			{
				free(windowState->visibilityRects);
				windowState->visibilityRects = NULL;
				return FALSE;
			}

			windowState->visibilityRects = newRect;

			if (Stream_GetRemainingLength(s) < windowState->numVisibilityRects * 8)
				return FALSE;


			for (i = 0; i < windowState->numVisibilityRects; i++)
			{
				Stream_Read_UINT16(s, windowState->visibilityRects[i].left);
				Stream_Read_UINT16(s, windowState->visibilityRects[i].top);
				Stream_Read_UINT16(s, windowState->visibilityRects[i].right);
				Stream_Read_UINT16(s,
				                   windowState->visibilityRects[i].bottom);
			}
		}
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_OVERLAY_DESCRIPTION)
	{
		if (!rail_read_unicode_string(s, &windowState->OverlayDescription))
			return FALSE;
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_ICON_OVERLAY_NULL)
	{

	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_TASKBAR_BUTTON)
	{
		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, windowState->TaskbarButton);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_ENFORCE_SERVER_ZORDER)
	{
		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, windowState->EnforceServerZOrder);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_APPBAR_STATE)
	{
		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, windowState->AppBarState);
	}

	if (orderInfo->fieldFlags & WINDOW_ORDER_FIELD_APPBAR_EDGE)
	{
		if (Stream_GetRemainingLength(s) < 1)
			return FALSE;

		Stream_Read_UINT8(s, windowState->AppBarEdge);
	}

	return TRUE;
}
