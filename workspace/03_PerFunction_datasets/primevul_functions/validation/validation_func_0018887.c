int rdp_recv_autodetect_request_packet(rdpRdp* rdp, wStream* s)
{
	AUTODETECT_REQ_PDU autodetectReqPdu;
	BOOL success = FALSE;

	if (Stream_GetRemainingLength(s) < 6)
		return -1;

	Stream_Read_UINT8(s, autodetectReqPdu.headerLength);
	Stream_Read_UINT8(s, autodetectReqPdu.headerTypeId);
	Stream_Read_UINT16(s, autodetectReqPdu.sequenceNumber);
	Stream_Read_UINT16(s, autodetectReqPdu.requestType);
	WLog_VRB(AUTODETECT_TAG,
	         "rdp_recv_autodetect_request_packet: headerLength=%" PRIu8 ", headerTypeId=%" PRIu8
	         ", sequenceNumber=%" PRIu16 ", requestType=%04" PRIx16 "",
	         autodetectReqPdu.headerLength, autodetectReqPdu.headerTypeId,
	         autodetectReqPdu.sequenceNumber, autodetectReqPdu.requestType);

	if (autodetectReqPdu.headerTypeId != TYPE_ID_AUTODETECT_REQUEST)
		return -1;

	switch (autodetectReqPdu.requestType)
	{
		case RDP_RTT_REQUEST_TYPE_CONTINUOUS:
		case RDP_RTT_REQUEST_TYPE_CONNECTTIME:

			success = autodetect_recv_rtt_measure_request(rdp, s, &autodetectReqPdu);
			break;

		case RDP_BW_START_REQUEST_TYPE_CONTINUOUS:
		case RDP_BW_START_REQUEST_TYPE_TUNNEL:
		case RDP_BW_START_REQUEST_TYPE_CONNECTTIME:

			success = autodetect_recv_bandwidth_measure_start(rdp, s, &autodetectReqPdu);
			break;

		case RDP_BW_PAYLOAD_REQUEST_TYPE:

			success = autodetect_recv_bandwidth_measure_payload(rdp, s, &autodetectReqPdu);
			break;

		case RDP_BW_STOP_REQUEST_TYPE_CONNECTTIME:
		case RDP_BW_STOP_REQUEST_TYPE_CONTINUOUS:
		case RDP_BW_STOP_REQUEST_TYPE_TUNNEL:

			success = autodetect_recv_bandwidth_measure_stop(rdp, s, &autodetectReqPdu);
			break;

		case 0x0840:
		case 0x0880:
		case 0x08C0:

			success = autodetect_recv_netchar_result(rdp, s, &autodetectReqPdu);
			break;

		default:
			break;
	}

	return success ? 0 : -1;
}
