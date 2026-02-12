void CConnectionTransportUDPBase::Received_ConnectionClosed( const CMsgSteamSockets_UDP_ConnectionClosed &msg, SteamNetworkingMicroseconds usecNow )
{


	bool bConnectionIDMatch =
		msg.to_connection_id() == ConnectionIDLocal()
		|| ( msg.to_connection_id() == 0 && msg.from_connection_id() && msg.from_connection_id() == m_connection.m_unConnectionIDRemote );
	if ( bConnectionIDMatch || BCheckGlobalSpamReplyRateLimit( usecNow ) )
	{

		CMsgSteamSockets_UDP_NoConnection msgReply;
		if ( msg.to_connection_id() )
			msgReply.set_from_connection_id( msg.to_connection_id() );
		if ( msg.from_connection_id() )
			msgReply.set_to_connection_id( msg.from_connection_id() );
		SendMsg( k_ESteamNetworkingUDPMsg_NoConnection, msgReply );
	}


	if ( !bConnectionIDMatch )
		return;


	m_connection.ConnectionState_ClosedByPeer( msg.reason_code(), msg.debug().c_str() );
}
