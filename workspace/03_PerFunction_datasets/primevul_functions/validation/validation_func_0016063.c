BOOL rdp_recv_confirm_active(rdpRdp* rdp, wStream* s, UINT16 pduLength)
{
	rdpSettings* settings;
	UINT16 lengthSourceDescriptor;
	UINT16 lengthCombinedCapabilities;
	UINT16 numberCapabilities;
	settings = rdp->settings;

	if (Stream_GetRemainingLength(s) < 10)
		return FALSE;

	Stream_Seek_UINT32(s);
	Stream_Seek_UINT16(s);
	Stream_Read_UINT16(s, lengthSourceDescriptor);
	Stream_Read_UINT16(s, lengthCombinedCapabilities);

	if (Stream_GetRemainingLength(s) < lengthSourceDescriptor + 4U)
		return FALSE;

	Stream_Seek(s, lengthSourceDescriptor);
	Stream_Read_UINT16(s, numberCapabilities);
	Stream_Seek(s, 2);
	if (!rdp_read_capability_sets(s, rdp->settings, numberCapabilities, lengthCombinedCapabilities))
		return FALSE;

	if (!settings->ReceivedCapabilities[CAPSET_TYPE_SURFACE_COMMANDS])
	{

		settings->SurfaceCommandsEnabled = FALSE;
		settings->SurfaceFrameMarkerEnabled = FALSE;
	}

	if (!settings->ReceivedCapabilities[CAPSET_TYPE_FRAME_ACKNOWLEDGE])
	{

		settings->FrameAcknowledge = 0;
	}

	if (!settings->ReceivedCapabilities[CAPSET_TYPE_BITMAP_CACHE_V3_CODEC_ID])
	{

		settings->BitmapCacheV3Enabled = FALSE;
	}

	if (!settings->ReceivedCapabilities[CAPSET_TYPE_BITMAP_CODECS])
	{

		settings->RemoteFxCodec = FALSE;
		settings->NSCodec = FALSE;
		settings->JpegCodec = FALSE;
	}

	if (!settings->ReceivedCapabilities[CAPSET_TYPE_MULTI_FRAGMENT_UPDATE])
	{

		settings->MultifragMaxRequestSize = FASTPATH_FRAGMENT_SAFE_SIZE;
	}

	if (!settings->ReceivedCapabilities[CAPSET_TYPE_LARGE_POINTER])
	{

		settings->LargePointerFlag = 0;
	}

	return tpkt_ensure_stream_consumed(s, pduLength);
}
