static BOOL rdp_read_input_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	UINT16 inputFlags;

	if (length < 88)
		return FALSE;

	Stream_Read_UINT16(s, inputFlags);
	Stream_Seek_UINT16(s);

	if (settings->ServerMode)
	{
		Stream_Read_UINT32(s, settings->KeyboardLayout);
		Stream_Read_UINT32(s, settings->KeyboardType);
		Stream_Read_UINT32(s, settings->KeyboardSubType);
		Stream_Read_UINT32(s, settings->KeyboardFunctionKey);
	}
	else
	{
		Stream_Seek_UINT32(s);
		Stream_Seek_UINT32(s);
		Stream_Seek_UINT32(s);
		Stream_Seek_UINT32(s);
	}

	Stream_Seek(s, 64);

	if (!settings->ServerMode)
	{
		if (inputFlags & INPUT_FLAG_FASTPATH_INPUT)
		{

		}
		else if (inputFlags & INPUT_FLAG_FASTPATH_INPUT2)
		{

		}
		else
		{

			settings->FastPathInput = FALSE;
		}

		if (inputFlags & TS_INPUT_FLAG_MOUSE_HWHEEL)
			settings->HasHorizontalWheel = TRUE;

		if (inputFlags & INPUT_FLAG_UNICODE)
			settings->UnicodeInput = TRUE;

		if (inputFlags & INPUT_FLAG_MOUSEX)
			settings->HasExtendedMouseEvent = TRUE;
	}

	return TRUE;
}
