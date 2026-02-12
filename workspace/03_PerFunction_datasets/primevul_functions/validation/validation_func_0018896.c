static BOOL autodetect_send_netchar_result(rdpContext* context, UINT16 sequenceNumber)
{
	wStream* s;
	s = rdp_message_channel_pdu_init(context->rdp);

	if (!s)
		return FALSE;

	WLog_VRB(AUTODETECT_TAG, "sending Bandwidth Network Characteristics Result PDU");

	if (context->rdp->autodetect->netCharBandwidth > 0)
	{
		Stream_Write_UINT8(s, 0x12);
		Stream_Write_UINT8(s, TYPE_ID_AUTODETECT_REQUEST);
		Stream_Write_UINT16(s, sequenceNumber);
		Stream_Write_UINT16(s, 0x08C0);
		Stream_Write_UINT32(s, context->rdp->autodetect->netCharBaseRTT);
		Stream_Write_UINT32(s,
		                    context->rdp->autodetect->netCharBandwidth);
		Stream_Write_UINT32(s,
		                    context->rdp->autodetect->netCharAverageRTT);
	}
	else
	{
		Stream_Write_UINT8(s, 0x0E);
		Stream_Write_UINT8(s, TYPE_ID_AUTODETECT_REQUEST);
		Stream_Write_UINT16(s, sequenceNumber);
		Stream_Write_UINT16(s, 0x0840);
		Stream_Write_UINT32(s, context->rdp->autodetect->netCharBaseRTT);
		Stream_Write_UINT32(s,
		                    context->rdp->autodetect->netCharAverageRTT);
	}

	return rdp_send_message_channel_pdu(context->rdp, s, SEC_AUTODETECT_REQ);
}
