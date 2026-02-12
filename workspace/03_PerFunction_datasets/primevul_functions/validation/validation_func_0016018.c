static BOOL rdp_read_remote_programs_capability_set(wStream* s, UINT16 length,
                                                    rdpSettings* settings)
{
	UINT32 railSupportLevel;

	if (length < 8)
		return FALSE;

	Stream_Read_UINT32(s, railSupportLevel);

	if ((railSupportLevel & RAIL_LEVEL_SUPPORTED) == 0)
	{
		if (settings->RemoteApplicationMode == TRUE)
		{

			settings->RemoteApplicationMode = FALSE;
		}
	}


	if (settings->RemoteApplicationMode)
		railSupportLevel |= RAIL_LEVEL_HANDSHAKE_EX_SUPPORTED;

	settings->RemoteApplicationSupportLevel =
	    railSupportLevel & settings->RemoteApplicationSupportMask;
	return TRUE;
}
