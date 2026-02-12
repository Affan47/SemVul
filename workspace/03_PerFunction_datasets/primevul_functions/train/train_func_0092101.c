bool CConnectionTransportUDP::BConnect( const netadr_t &netadrRemote, SteamDatagramErrMsg &errMsg )
{


	Assert( !m_pSocket );
	m_pSocket = OpenUDPSocketBoundToHost( netadrRemote, CRecvPacketCallback( PacketReceived, this ), errMsg );
	if ( !m_pSocket )
		return false;
	return true;
}
