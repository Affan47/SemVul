bool CConnectionTransportUDP::SendPacketGather( int nChunks, const iovec *pChunks, int cbSendTotal )
{

	if ( !m_pSocket )
	{
		AssertMsg( false, "Attemt to send packet, but socket has been closed!" );
		return false;
	}


	m_connection.m_statsEndToEnd.TrackSentPacket( cbSendTotal );


	return m_pSocket->BSendRawPacketGather( nChunks, pChunks );
}
