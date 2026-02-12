void CSteamNetworkListenSocketDirectUDP::Received_ConnectRequest( const CMsgSteamSockets_UDP_ConnectRequest &msg, const netadr_t &adrFrom, int cbPkt, SteamNetworkingMicroseconds usecNow )
{
	SteamDatagramErrMsg errMsg;


	uint16 nTimeThen = uint32( msg.challenge() );
	uint16 nElapsed = GetChallengeTime( usecNow ) - nTimeThen;
	if ( nElapsed > GetChallengeTime( 4*k_nMillion ) )
	{
		ReportBadPacket( "ConnectRequest", "Challenge too old." );
		return;
	}


	if ( GenerateChallenge( nTimeThen, adrFrom ) != msg.challenge() )
	{
		ReportBadPacket( "ConnectRequest", "Incorrect challenge.  Could be spoofed." );
		return;
	}

	uint32 unClientConnectionID = msg.client_connection_id();
	if ( unClientConnectionID == 0 )
	{
		ReportBadPacket( "ConnectRequest", "Missing connection ID" );
		return;
	}


	SteamNetworkingIdentity identityRemote;
	bool bIdentityInCert = true;
	{


		int r = SteamNetworkingIdentityFromSignedCert( identityRemote, msg.cert(), errMsg );
		if ( r < 0 )
		{
			ReportBadPacket( "ConnectRequest", "Bad identity in cert.  %s", errMsg );
			return;
		}
		if ( r == 0 )
		{

			bIdentityInCert = false;
			r = SteamNetworkingIdentityFromProtobuf( identityRemote, msg, identity_string, legacy_identity_binary, legacy_client_steam_id, errMsg );
			if ( r < 0 )
			{
				ReportBadPacket( "ConnectRequest", "Bad identity.  %s", errMsg );
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
		adrFrom.GetIPV6( addr.m_ipv6 );
		addr.m_port = adrFrom.GetPort();

		if ( identityRemote.IsLocalHost() )
		{
			if ( m_connectionConfig.m_IP_AllowWithoutAuth.Get() == 0 )
			{

				ReportBadPacket( "ConnectRequest", "Unauthenticated connections not allowed." );
				return;
			}


			identityRemote.SetIPAddr( addr );
		}
		else
		{


			if ( !bIdentityInCert )
			{

				ReportBadPacket( "ConnectRequest", "Cannot use specific IP address." );
				return;
			}
		}
	}


	int h = m_mapChildConnections.Find( RemoteConnectionKey_t{ identityRemote, unClientConnectionID } );
	if ( h != m_mapChildConnections.InvalidIndex() )
	{
		CSteamNetworkConnectionBase *pOldConn = m_mapChildConnections[ h ];
		Assert( pOldConn->m_identityRemote == identityRemote );


		ReportBadPacket( "ConnectRequest", "Rejecting connection request from %s at %s, connection ID %u.  That steamID/ConnectionID pair already has a connection [%s]\n",
			SteamNetworkingIdentityRender( identityRemote ).c_str(), CUtlNetAdrRender( adrFrom ).String(), unClientConnectionID, pOldConn->GetDescription()
		);

		CMsgSteamSockets_UDP_ConnectionClosed msgReply;
		msgReply.set_to_connection_id( unClientConnectionID );
		msgReply.set_reason_code( k_ESteamNetConnectionEnd_Misc_Generic );
		msgReply.set_debug( "A connection with that ID already exists." );
		SendPaddedMsg( k_ESteamNetworkingUDPMsg_ConnectionClosed, msgReply, adrFrom );
		return;
	}

	CSteamNetworkConnectionUDP *pConn = new CSteamNetworkConnectionUDP( m_pSteamNetworkingSocketsInterface );


	if ( !pConn->BBeginAccept( this, adrFrom, m_pSock, identityRemote, unClientConnectionID, msg.cert(), msg.crypt(), errMsg ) )
	{
		SpewWarning( "Failed to accept connection from %s.  %s\n", CUtlNetAdrRender( adrFrom ).String(), errMsg );
		pConn->ConnectionDestroySelfNow();
		return;
	}

	pConn->m_statsEndToEnd.TrackRecvPacket( cbPkt, usecNow );


	if ( msg.has_ping_est_ms() )
	{
		if ( msg.ping_est_ms() > 1500 )
		{
			SpewWarning( "[%s] Ignoring really large ping estimate %u in connect request", pConn->GetDescription(), msg.has_ping_est_ms() );
		}
		else
		{
			pConn->m_statsEndToEnd.m_ping.ReceivedPing( msg.ping_est_ms(), usecNow );
		}
	}


	if ( msg.has_my_timestamp() )
	{
		pConn->m_ulHandshakeRemoteTimestamp = msg.my_timestamp();
		pConn->m_usecWhenReceivedHandshakeRemoteTimestamp = usecNow;
	}
}
