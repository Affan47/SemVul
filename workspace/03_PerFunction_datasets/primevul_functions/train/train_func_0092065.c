void CConnectionTransportUDP::SendConnectOK( SteamNetworkingMicroseconds usecNow )
{
	Assert( ConnectionIDLocal() );
	Assert( ConnectionIDRemote() );
	Assert( ListenSocket() );

	Assert( m_connection.GetSignedCertLocal().has_cert() );
	Assert( m_connection.GetSignedCryptLocal().has_info() );

	CMsgSteamSockets_UDP_ConnectOK msg;
	msg.set_client_connection_id( ConnectionIDRemote() );
	msg.set_server_connection_id( ConnectionIDLocal() );
	*msg.mutable_cert() = m_connection.GetSignedCertLocal();
	*msg.mutable_crypt() = m_connection.GetSignedCryptLocal();


	if ( !m_connection.BCertHasIdentity() )
	{
		SteamNetworkingIdentityToProtobuf( IdentityLocal(), msg, identity_string, legacy_identity_binary, legacy_server_steam_id );
	}
	else
	{

		if ( IdentityLocal().GetSteamID64() )
			msg.set_legacy_server_steam_id( IdentityLocal().GetSteamID64() );
	}


	if ( m_connection.m_usecWhenReceivedHandshakeRemoteTimestamp )
	{
		SteamNetworkingMicroseconds usecElapsed = usecNow - m_connection.m_usecWhenReceivedHandshakeRemoteTimestamp;
		Assert( usecElapsed >= 0 );
		if ( usecElapsed < 4*k_nMillion )
		{
			msg.set_your_timestamp( m_connection.m_ulHandshakeRemoteTimestamp );
			msg.set_delay_time_usec( usecElapsed );
		}
		else
		{
			SpewWarning( "Discarding handshake timestamp that's %lldms old, not sending in ConnectOK\n", usecElapsed/1000 );
			m_connection.m_usecWhenReceivedHandshakeRemoteTimestamp = 0;
		}
	}


	SendMsg( k_ESteamNetworkingUDPMsg_ConnectOK, msg );
}
