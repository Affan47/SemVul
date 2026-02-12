static BOOL autodetect_recv_netchar_result(rdpRdp* rdp, wStream* s,
                                           AUTODETECT_REQ_PDU* autodetectReqPdu)
{
	BOOL success = TRUE;

	switch (autodetectReqPdu->requestType)
	{
		case 0x0840:


			if ((autodetectReqPdu->headerLength != 0x0E) || (Stream_GetRemainingLength(s) < 8))
				return FALSE;

			Stream_Read_UINT32(s, rdp->autodetect->netCharBaseRTT);
			Stream_Read_UINT32(s, rdp->autodetect->netCharAverageRTT);
			break;

		case 0x0880:


			if ((autodetectReqPdu->headerLength != 0x0E) || (Stream_GetRemainingLength(s) < 8))
				return FALSE;

			Stream_Read_UINT32(s, rdp->autodetect->netCharBandwidth);
			Stream_Read_UINT32(s, rdp->autodetect->netCharAverageRTT);
			break;

		case 0x08C0:


			if ((autodetectReqPdu->headerLength != 0x12) || (Stream_GetRemainingLength(s) < 12))
				return FALSE;

			Stream_Read_UINT32(s, rdp->autodetect->netCharBaseRTT);
			Stream_Read_UINT32(s, rdp->autodetect->netCharBandwidth);
			Stream_Read_UINT32(s, rdp->autodetect->netCharAverageRTT);
			break;
	}

	WLog_VRB(AUTODETECT_TAG,
	         "received Network Characteristics Result PDU -> baseRTT=%" PRIu32
	         ", bandwidth=%" PRIu32 ", averageRTT=%" PRIu32 "",
	         rdp->autodetect->netCharBaseRTT, rdp->autodetect->netCharBandwidth,
	         rdp->autodetect->netCharAverageRTT);
	IFCALLRET(rdp->autodetect->NetworkCharacteristicsResult, success, rdp->context,
	          autodetectReqPdu->sequenceNumber);
	return success;
}
