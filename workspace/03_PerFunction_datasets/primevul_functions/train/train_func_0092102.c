bool CConnectionTransportUDP::BAccept( CSharedSocket *pSharedSock, const netadr_t &netadrRemote, SteamDatagramErrMsg &errMsg )
{

	m_pSocket = pSharedSock->AddRemoteHost( netadrRemote, CRecvPacketCallback( PacketReceived, this ) );
	if ( !m_pSocket )
	{

		V_strcpy_safe( errMsg, "Unable to create a bound socket on the shared socket." );
		return false;
	}

	return true;
}
