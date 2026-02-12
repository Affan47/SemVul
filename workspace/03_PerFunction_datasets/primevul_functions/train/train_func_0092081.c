void CConnectionTransportUDPBase::Received_NoConnection( const CMsgSteamSockets_UDP_NoConnection &msg, SteamNetworkingMicroseconds usecNow )
{

	if ( msg.to_connection_id() != ConnectionIDLocal() || msg.from_connection_id() != m_connection.m_unConnectionIDRemote )
	{
		ReportBadUDPPacketFromConnectionPeer( "NoConnection", "Old/incorrect connection ID.  Message is for a stale connection, or is spoofed.  Ignoring." );
		return;
	}


	m_connection.ConnectionState_ClosedByPeer( k_ESteamNetConnectionEnd_Misc_PeerSentNoConnection, "Received unexpected 'no connection' from peer");
}
