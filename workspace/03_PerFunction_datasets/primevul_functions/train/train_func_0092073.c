bool CConnectionTransportUDPBase::SendDataPacket( SteamNetworkingMicroseconds usecNow )
{

	UDPSendPacketContext_t ctx( usecNow, "data" );
	ctx.Populate( sizeof(UDPDataMsgHdr), k_EStatsReplyRequest_NothingToSend, this );


	return m_connection.SNP_SendPacket( this, ctx );
}
