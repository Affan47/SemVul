static BOOL rfx_process_message_channels(RFX_CONTEXT* context, wStream* s)
{
	BYTE channelId;
	BYTE numChannels;
	context->decodedHeaderBlocks &= ~_RFX_DECODED_CHANNELS;

	if (Stream_GetRemainingLength(s) < 1)
	{
		WLog_ERR(TAG, "RfxMessageChannels packet too small");
		return FALSE;
	}

	Stream_Read_UINT8(s, numChannels);


	if (numChannels < 1)
	{
		WLog_ERR(TAG, "no channels announced");
		return FALSE;
	}

	if (Stream_GetRemainingLength(s) < (size_t)(numChannels * 5))
	{
		WLog_ERR(TAG, "RfxMessageChannels packet too small for numChannels=%" PRIu8 "",
		         numChannels);
		return FALSE;
	}


	Stream_Read_UINT8(s, channelId);

	if (channelId != 0x00)
	{
		WLog_ERR(TAG, "channelId:0x%02" PRIX8 ", expected:0x00", channelId);
		return FALSE;
	}

	Stream_Read_UINT16(s, context->width);
	Stream_Read_UINT16(s, context->height);

	if (!context->width || !context->height)
	{
		WLog_ERR(TAG, "%s: invalid channel with/height: %" PRIu16 "x%" PRIu16 "", __FUNCTION__,
		         context->width, context->height);
		return FALSE;
	}


	Stream_Seek(s, 5 * (numChannels - 1));
	WLog_Print(context->priv->log, WLOG_DEBUG,
	           "numChannels %" PRIu8 " id %" PRIu8 ", %" PRIu16 "x%" PRIu16 ".", numChannels,
	           channelId, context->width, context->height);
	context->decodedHeaderBlocks |= _RFX_DECODED_CHANNELS;
	return TRUE;
}
