static BOOL rdp_write_input_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;
	UINT16 inputFlags;

	if (!Stream_EnsureRemainingCapacity(s, 128))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;
	inputFlags = INPUT_FLAG_SCANCODES;

	if (settings->FastPathInput)
	{
		inputFlags |= INPUT_FLAG_FASTPATH_INPUT;
		inputFlags |= INPUT_FLAG_FASTPATH_INPUT2;
	}

	if (settings->HasHorizontalWheel)
		inputFlags |= TS_INPUT_FLAG_MOUSE_HWHEEL;

	if (settings->UnicodeInput)
		inputFlags |= INPUT_FLAG_UNICODE;

	if (settings->HasExtendedMouseEvent)
		inputFlags |= INPUT_FLAG_MOUSEX;

	Stream_Write_UINT16(s, inputFlags);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT32(s, settings->KeyboardLayout);
	Stream_Write_UINT32(s, settings->KeyboardType);
	Stream_Write_UINT32(s, settings->KeyboardSubType);
	Stream_Write_UINT32(s, settings->KeyboardFunctionKey);
	Stream_Zero(s, 64);
	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_INPUT);
	return TRUE;
}
