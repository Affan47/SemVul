static BOOL rdp_read_general_capability_set(wStream* s, UINT16 length, rdpSettings* settings)
{
	UINT16 extraFlags;
	BYTE refreshRectSupport;
	BYTE suppressOutputSupport;

	if (length < 24)
		return FALSE;

	if (settings->ServerMode)
	{
		Stream_Read_UINT16(s, settings->OsMajorType);
		Stream_Read_UINT16(s, settings->OsMinorType);
	}
	else
	{
		Stream_Seek_UINT16(s);
		Stream_Seek_UINT16(s);
	}

	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Read_UINT16(s, extraFlags);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Seek_UINT16(s);
	Stream_Read_UINT8(s, refreshRectSupport);
	Stream_Read_UINT8(s, suppressOutputSupport);
	settings->NoBitmapCompressionHeader = (extraFlags & NO_BITMAP_COMPRESSION_HDR) ? TRUE : FALSE;
	settings->LongCredentialsSupported = (extraFlags & LONG_CREDENTIALS_SUPPORTED) ? TRUE : FALSE;

	if (!(extraFlags & FASTPATH_OUTPUT_SUPPORTED))
		settings->FastPathOutput = FALSE;

	if (!(extraFlags & ENC_SALTED_CHECKSUM))
		settings->SaltedChecksum = FALSE;

	if (!settings->ServerMode)
	{


		if (!refreshRectSupport)
			settings->RefreshRect = FALSE;

		if (!suppressOutputSupport)
			settings->SuppressOutput = FALSE;
	}

	return TRUE;
}
