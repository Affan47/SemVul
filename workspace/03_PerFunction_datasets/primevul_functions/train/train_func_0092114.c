bool CSteamNetworkConnectionUDP::BInitConnect( const SteamNetworkingIPAddr &addressRemote, int nOptions, const SteamNetworkingConfigValue_t *pOptions, SteamDatagramErrMsg &errMsg )
{
	AssertMsg( !m_pTransport, "Trying to connect when we already have a socket?" );


	Assert( !m_pParentListenSocket );
	Assert( !m_bConnectionInitiatedRemotely );

	netadr_t netadrRemote;
	SteamNetworkingIPAddrToNetAdr( netadrRemote, addressRemote );


	Assert( m_identityRemote.IsInvalid() );
	m_identityRemote.Clear();


	if ( m_identityLocal.IsInvalid() )
	{


		m_identityLocal = m_pSteamNetworkingSocketsInterface->InternalGetIdentity();
		if ( m_identityLocal.IsInvalid())
		{


			if ( m_connectionConfig.m_IP_AllowWithoutAuth.Get() == 0 )
			{
				V_strcpy_safe( errMsg, "Unable to determine local identity, and auth required.  Not logged in?" );
				return false;
			}

			m_identityLocal.SetLocalHost();
		}
	}


	CConnectionTransportUDP *pTransport = new CConnectionTransportUDP( *this );
	if ( !pTransport->BConnect( netadrRemote, errMsg ) )
	{
		pTransport->TransportDestroySelfNow();
		return false;
	}
	m_pTransport = pTransport;


	SteamNetworkingMicroseconds usecNow = SteamNetworkingSockets_GetLocalTimestamp();
	if ( !CSteamNetworkConnectionBase::BInitConnection( usecNow, nOptions, pOptions, errMsg ) )
	{
		DestroyTransport();
		return false;
	}


	return BConnectionState_Connecting( usecNow, errMsg );
}
