static BOOL rdp_write_general_capability_set(wStream* s, const rdpSettings* settings)
{
	size_t header;
	UINT16 extraFlags;

	if (!Stream_EnsureRemainingCapacity(s, 64))
		return FALSE;

	header = rdp_capability_set_start(s);
	if (header > UINT16_MAX)
		return FALSE;
	extraFlags = 0;

	if (settings->LongCredentialsSupported)
		extraFlags |= LONG_CREDENTIALS_SUPPORTED;

	if (settings->NoBitmapCompressionHeader)
		extraFlags |= NO_BITMAP_COMPRESSION_HDR;

	if (settings->AutoReconnectionEnabled)
		extraFlags |= AUTORECONNECT_SUPPORTED;

	if (settings->FastPathOutput)
		extraFlags |= FASTPATH_OUTPUT_SUPPORTED;

	if (settings->SaltedChecksum)
		extraFlags |= ENC_SALTED_CHECKSUM;

	if ((settings->OsMajorType > UINT16_MAX) || (settings->OsMinorType > UINT16_MAX))
	{
		WLog_ERR(TAG,
		         "OsMajorType=%08" PRIx32 ", OsMinorType=%08" PRIx32
		         " they need to be smaller %04" PRIx16,
		         settings->OsMajorType, settings->OsMinorType, UINT16_MAX);
		return FALSE;
	}
	Stream_Write_UINT16(s, (UINT16)settings->OsMajorType);
	Stream_Write_UINT16(s, (UINT16)settings->OsMinorType);
	Stream_Write_UINT16(s, CAPS_PROTOCOL_VERSION);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, extraFlags);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT16(s, 0);
	Stream_Write_UINT8(s, settings->RefreshRect ? 1 : 0);
	Stream_Write_UINT8(s, settings->SuppressOutput ? 1 : 0);
	rdp_capability_set_finish(s, (UINT16)header, CAPSET_TYPE_GENERAL);
	return TRUE;
}
