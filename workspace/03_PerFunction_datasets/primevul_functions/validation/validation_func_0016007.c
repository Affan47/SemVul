static BOOL rdp_read_multifragment_update_capability_set(wStream* s, UINT16 length,
                                                         rdpSettings* settings)
{
	UINT32 multifragMaxRequestSize;

	if (length < 8)
		return FALSE;

	Stream_Read_UINT32(s, multifragMaxRequestSize);

	if (settings->ServerMode)
	{


		if (multifragMaxRequestSize < FASTPATH_MAX_PACKET_SIZE)
			multifragMaxRequestSize = FASTPATH_FRAGMENT_SAFE_SIZE;

		if (settings->RemoteFxCodec)
		{


			if (multifragMaxRequestSize < settings->MultifragMaxRequestSize)
			{


				settings->RemoteFxCodec = FALSE;
				settings->MultifragMaxRequestSize = multifragMaxRequestSize;
			}
			else
			{

			}
		}
		else
		{
			settings->MultifragMaxRequestSize = multifragMaxRequestSize;
		}
	}
	else
	{


		if (multifragMaxRequestSize > settings->MultifragMaxRequestSize)
			settings->MultifragMaxRequestSize = multifragMaxRequestSize;
	}

	return TRUE;
}
