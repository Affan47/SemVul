INLINE BOOL gdi_PtInRect(HGDI_RECT rc, INT32 x, INT32 y)
{


	if (x >= rc->left && x <= rc->right)
	{
		if (y >= rc->top && y <= rc->bottom)
		{
			return TRUE;
		}
	}

	return FALSE;
}
