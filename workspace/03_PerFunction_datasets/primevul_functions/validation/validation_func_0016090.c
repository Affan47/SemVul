static BOOL rdp_write_multifragment_update_capability_set(wStream* s, rdpSettings* settings)
{
	size_t header;

	if (!Stream_EnsureRemainingCapacity(s, 32))
		return FALSE;

	if (settings->ServerMode && settings->MultifragMaxRequestSize == 0)
	{


		UINT32 tileNumX = (settings->DesktopWidth + 63) / 64;
		UINT32 tileNumY = (settings->DesktopHeight + 63) / 64;
		settings->MultifragMaxRequestSize = tileNumX * tileNumY * 16384;

		settings->MultifragMaxRequestSize += 16384;
	}

	header = rdp_capability_set_start(s);
	Stream_Write_UINT32(s, settings->MultifragMaxRequestSize);
	rdp_capability_set_finish(s, header, CAPSET_TYPE_MULTI_FRAGMENT_UPDATE);
	return TRUE;
}
