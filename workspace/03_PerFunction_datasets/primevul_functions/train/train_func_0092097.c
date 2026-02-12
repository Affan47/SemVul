void CConnectionTransportUDP::Received_ChallengeReply( const CMsgSteamSockets_UDP_ChallengeReply &msg, SteamNetworkingMicroseconds usecNow )
{

	if ( ListenSocket() )
	{
		ReportBadUDPPacketFromConnectionPeer( "ChallengeReply", "Shouldn't be receiving this unless on accepted connections, only connections initiated locally." );
		return;
	}


	if ( ConnectionState() != k_ESteamNetworkingConnectionState_Connecting )
		return;


	if ( msg.connection_id() != ConnectionIDLocal() )
	{
		ReportBadUDPPacketFromConnectionPeer( "ChallengeReply", "Incorrect connection ID.  Message is stale or could be spoofed, ignoring." );
		return;
	}
	if ( msg.protocol_version() < k_nMinRequiredProtocolVersion )
	{
		m_connection.ConnectionState_ProblemDetectedLocally( k_ESteamNetConnectionEnd_Misc_Generic, "Peer is running old software and needs to be udpated" );
		return;
	}


	if ( msg.has_your_timestamp() )
	{
		SteamNetworkingMicroseconds usecElapsed = usecNow - (SteamNetworkingMicroseconds)msg.your_timestamp();
		if ( usecElapsed < 0 || usecElapsed > 2*k_nMillion )
		{
			SpewWarning( "Ignoring weird timestamp %llu in ChallengeReply, current time is %llu.\n", (unsigned long long)msg.your_timestamp(), usecNow );
		}
		else
		{
			int nPing = (usecElapsed + 500 ) / 1000;
			m_connection.m_statsEndToEnd.m_ping.ReceivedPing( nPing, usecNow );
		}
	}


	if ( !m_connection.GetSignedCertLocal().has_cert() || !m_connection.GetSignedCryptLocal().has_info() )
	{
		m_connection.ConnectionState_ProblemDetectedLocally( k_ESteamNetConnectionEnd_Misc_InternalError, "Tried to connect request, but crypt not ready" );
		return;
	}


	m_connection.m_statsEndToEnd.m_nPeerProtocolVersion = msg.protocol_version();


	CMsgSteamSockets_UDP_ConnectRequest msgConnectRequest;
	msgConnectRequest.set_client_connection_id( ConnectionIDLocal() );
	msgConnectRequest.set_challenge( msg.challenge() );
	msgConnectRequest.set_my_timestamp( usecNow );
	if ( m_connection.m_statsEndToEnd.m_ping.m_nSmoothedPing >= 0 )
		msgConnectRequest.set_ping_est_ms( m_connection.m_statsEndToEnd.m_ping.m_nSmoothedPing );
	*msgConnectRequest.mutable_cert() = m_connection.GetSignedCertLocal();
	*msgConnectRequest.mutable_crypt() = m_connection.GetSignedCryptLocal();


	if ( !m_connection.BCertHasIdentity() )
	{
		SteamNetworkingIdentityToProtobuf( IdentityLocal(), msgConnectRequest, identity_string, legacy_identity_binary, legacy_client_steam_id );
	}
	else
	{

		if ( IdentityLocal().GetSteamID64() )
			msgConnectRequest.set_legacy_client_steam_id( IdentityLocal().GetSteamID64() );
	}


	SendMsg( k_ESteamNetworkingUDPMsg_ConnectRequest, msgConnectRequest );


	m_connection.SentEndToEndConnectRequest( usecNow );


	m_connection.m_statsEndToEnd.TrackSentPingRequest( usecNow, false );
}
