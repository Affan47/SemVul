static BOOL autodetect_send_bandwidth_measure_results(rdpRdp* rdp, UINT16 responseType,
                                                      UINT16 sequenceNumber)
{
	BOOL success = TRUE;
	wStream* s;
	UINT64 timeDelta;

	timeDelta = GetTickCount64() - rdp->autodetect->bandwidthMeasureStartTime;

	s = rdp_message_channel_pdu_init(rdp);

	if (!s)
		return FALSE;

	WLog_VRB(AUTODETECT_TAG,
	         "sending Bandwidth Measure Results PDU -> timeDelta=%" PRIu32 ", byteCount=%" PRIu32
	         "",
	         timeDelta, rdp->autodetect->bandwidthMeasureByteCount);
	Stream_Write_UINT8(s, 0x0E);
	Stream_Write_UINT8(s, TYPE_ID_AUTODETECT_RESPONSE);
	Stream_Write_UINT16(s, sequenceNumber);
	Stream_Write_UINT16(s, responseType);
	Stream_Write_UINT32(s, timeDelta);
	Stream_Write_UINT32(s, rdp->autodetect->bandwidthMeasureByteCount);
	IFCALLRET(rdp->autodetect->ClientBandwidthMeasureResult, success, rdp->context,
	          rdp->autodetect);

	if (!success)
		return FALSE;

	return rdp_send_message_channel_pdu(rdp, s, SEC_AUTODETECT_RSP);
}
