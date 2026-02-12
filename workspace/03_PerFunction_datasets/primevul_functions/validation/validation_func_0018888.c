static BOOL autodetect_send_netchar_sync(rdpRdp* rdp, UINT16 sequenceNumber)
{
	wStream* s;

	s = rdp_message_channel_pdu_init(rdp);

	if (!s)
		return FALSE;

	WLog_VRB(AUTODETECT_TAG,
	         "sending Network Characteristics Sync PDU -> bandwidth=%" PRIu32 ", rtt=%" PRIu32 "",
	         rdp->autodetect->netCharBandwidth, rdp->autodetect->netCharAverageRTT);
	Stream_Write_UINT8(s, 0x0E);
	Stream_Write_UINT8(s, TYPE_ID_AUTODETECT_RESPONSE);
	Stream_Write_UINT16(s, sequenceNumber);
	Stream_Write_UINT16(s, RDP_NETCHAR_SYNC_RESPONSE_TYPE);
	Stream_Write_UINT32(s, rdp->autodetect->netCharBandwidth);
	Stream_Write_UINT32(s, rdp->autodetect->netCharAverageRTT);
	return rdp_send_message_channel_pdu(rdp, s, SEC_AUTODETECT_RSP);
}
