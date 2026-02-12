void CConnectionTransportUDP::Received_ConnectOK( const CMsgSteamSockets_UDP_ConnectOK &msg, SteamNetworkingMicroseconds usecNow )
{
	SteamDatagramErrMsg errMsg;


	if ( ListenSocket() )
	{
		ReportBadUDPPacketFromConnectionPeer( "ConnectOK", "Shouldn't be receiving this unless on accepted connections, only connections initiated locally." );
		return;
	}


	if ( msg.client_connection_id() != ConnectionIDLocal() )
	{
		ReportBadUDPPacketFromConnectionPeer( "ConnectOK", "Incorrect connection ID.  Message is stale or could be spoofed, ignoring." );
		return;
	}


	SteamNetworkingIdentity identityRemote;
	bool bIdentityInCert = true;
	{


		int r = SteamNetworkingIdentityFromSignedCert( identityRemote, msg.cert(), errMsg );
		if ( r < 0 )
		{
			ReportBadUDPPacketFromConnectionPeer( "ConnectRequest", "Bad identity in cert.  %s", errMsg );
			return;
		}
		if ( r == 0 )
		{

			bIdentityInCert = false;
			r = SteamNetworkingIdentityFromProtobuf( identityRemote, msg, identity_string, legacy_identity_binary, legacy_server_steam_id, errMsg );
			if ( r < 0 )
			{
				ReportBadUDPPacketFromConnectionPeer( "ConnectRequest", "Bad identity.  %s", errMsg );
				return;
			}
			if ( r == 0 )
			{

				identityRemote.SetLocalHost();
			}
		}
	}
	Assert( !identityRemote.IsInvalid() );


	if ( identityRemote.m_eType == k_ESteamNetworkingIdentityType_IPAddress )
	{
		SteamNetworkingIPAddr addr;
		const netadr_t &adrFrom = m_pSocket->GetRemoteHostAddr();
		adrFrom.GetIPV6( addr.m_ipv6 );
		addr.m_port = adrFrom.GetPort();

		if ( identityRemote.IsLocalHost() )
		{
			if ( m_connection.m_connectionConfig.m_IP_AllowWithoutAuth.Get() == 0 )
			{

				ReportBadUDPPacketFromConnectionPeer( "ConnectOK", "Unauthenticated connections not allowed." );
				return;
			}


			identityRemote.SetIPAddr( addr );
		}
		else
		{


			if ( !bIdentityInCert )
			{

				ReportBadPacket( "ConnectOK", "Cannot use specific IP address." );
				return;
			}
		}
	}


	if ( !m_connection.m_identityRemote.IsInvalid() && !( m_connection.m_identityRemote == identityRemote ) )
	{
		ReportBadUDPPacketFromConnectionPeer( "ConnectOK", "server_steam_id doesn't match who we expect to be connecting to!" );
		return;
	}


	if ( msg.has_your_timestamp() )
	{
		SteamNetworkingMicroseconds usecElapsed = usecNow - (SteamNetworkingMicroseconds)msg.your_timestamp() - msg.delay_time_usec();
		if ( usecElapsed < 0 || usecElapsed > 2*k_nMillion )
		{
			SpewWarning( "Ignoring weird timestamp %llu in ConnectOK, current time is %llu, remote delay was %lld.\n", (unsigned long long)msg.your_timestamp(), usecNow, (long long)msg.delay_time_usec() );
		}
		else
		{
			int nPing = (usecElapsed + 500 ) / 1000;
			m_connection.m_statsEndToEnd.m_ping.ReceivedPing( nPing, usecNow );
		}
	}


	switch ( ConnectionState() )
	{
		case k_ESteamNetworkingConnectionState_Dead:
		case k_ESteamNetworkingConnectionState_None:
		case k_ESteamNetworkingConnectionState_FindingRoute:
		default:
			Assert( false );
			return;

		case k_ESteamNetworkingConnectionState_ClosedByPeer:
		case k_ESteamNetworkingConnectionState_FinWait:
		case k_ESteamNetworkingConnectionState_ProblemDetectedLocally:
			SendConnectionClosedOrNoConnection();
			return;

		case k_ESteamNetworkingConnectionState_Linger:
		case k_ESteamNetworkingConnectionState_Connected:


			return;

		case k_ESteamNetworkingConnectionState_Connecting:
			break;
	}


	m_connection.m_unConnectionIDRemote = msg.server_connection_id();
	if ( ( m_connection.m_unConnectionIDRemote & 0xffff ) == 0 )
	{
		m_connection.ConnectionState_ProblemDetectedLocally( k_ESteamNetConnectionEnd_Remote_BadCrypt, "Didn't send valid connection ID" );
		return;
	}

	m_connection.m_identityRemote = identityRemote;


	if ( !m_connection.BRecvCryptoHandshake( msg.cert(), msg.crypt(), false ) )
	{
		Assert( ConnectionState() == k_ESteamNetworkingConnectionState_ProblemDetectedLocally );
		ReportBadUDPPacketFromConnectionPeer( "ConnectOK", "Failed crypto init.  %s", m_connection.m_szEndDebug );
		return;
	}


	m_connection.ConnectionState_Connected( usecNow );
}
