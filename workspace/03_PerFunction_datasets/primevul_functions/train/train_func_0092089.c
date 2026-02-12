bool CSteamNetworkConnectionUDP::BBeginAccept(
	CSteamNetworkListenSocketDirectUDP *pParent,
	const netadr_t &adrFrom,
	CSharedSocket *pSharedSock,
	const SteamNetworkingIdentity &identityRemote,
	uint32 unConnectionIDRemote,
	const CMsgSteamDatagramCertificateSigned &msgCert,
	const CMsgSteamDatagramSessionCryptInfoSigned &msgCryptSessionInfo,
	SteamDatagramErrMsg &errMsg
)
{
	AssertMsg( !m_pTransport, "Trying to accept when we already have transport?" );


	CConnectionTransportUDP *pTransport = new CConnectionTransportUDP( *this );
	if ( !pTransport->BAccept( pSharedSock, adrFrom, errMsg ) )
	{
		pTransport->TransportDestroySelfNow();
		return false;
	}
	m_pTransport = pTransport;

	m_identityRemote = identityRemote;


	Assert( !m_identityRemote.IsInvalid() );

	m_unConnectionIDRemote = unConnectionIDRemote;
	if ( !pParent->BAddChildConnection( this, errMsg ) )
		return false;


	SteamNetworkingMicroseconds usecNow = SteamNetworkingSockets_GetLocalTimestamp();
	if ( !CSteamNetworkConnectionBase::BInitConnection( usecNow, 0, nullptr, errMsg ) )
	{
		DestroyTransport();
		return false;
	}


	if ( !BRecvCryptoHandshake( msgCert, msgCryptSessionInfo, true ) )
	{
		DestroyTransport();
		Assert( GetState() == k_ESteamNetworkingConnectionState_ProblemDetectedLocally );
		V_sprintf_safe( errMsg, "Failed crypto init.  %s", m_szEndDebug );
		return false;
	}


	return BConnectionState_Connecting( usecNow, errMsg );
}
