static BOOL autodetect_send_bandwidth_measure_stop(rdpContext* context, UINT16 payloadLength,
                                                   UINT16 sequenceNumber, UINT16 requestType)
{
	wStream* s;
	UCHAR* buffer = NULL;
	BOOL bResult = FALSE;
	s = rdp_message_channel_pdu_init(context->rdp);

	if (!s)
		return FALSE;

	WLog_VRB(AUTODETECT_TAG, "sending Bandwidth Measure Stop PDU -> payloadLength=%" PRIu16 "",
	         payloadLength);

	payloadLength &= ~3;
	Stream_Write_UINT8(s, requestType == RDP_BW_STOP_REQUEST_TYPE_CONNECTTIME
	                          ? 0x08
	                          : 0x06);
	Stream_Write_UINT8(s, TYPE_ID_AUTODETECT_REQUEST);
	Stream_Write_UINT16(s, sequenceNumber);
	Stream_Write_UINT16(s, requestType);

	if (requestType == RDP_BW_STOP_REQUEST_TYPE_CONNECTTIME)
	{
		Stream_Write_UINT16(s, payloadLength);

		if (payloadLength > 0)
		{
			if (!Stream_EnsureRemainingCapacity(s, payloadLength))
			{
				Stream_Release(s);
				return FALSE;
			}


			buffer = malloc(payloadLength);

			if (NULL == buffer)
			{
				Stream_Release(s);
				return FALSE;
			}

			winpr_RAND(buffer, payloadLength);
			Stream_Write(s, buffer, payloadLength);
		}
	}

	bResult = rdp_send_message_channel_pdu(context->rdp, s, SEC_AUTODETECT_REQ);
	free(buffer);
	return bResult;
}
