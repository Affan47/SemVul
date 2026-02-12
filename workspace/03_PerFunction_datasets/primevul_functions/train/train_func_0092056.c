CSteamNetworkListenSocketDirectUDP::~CSteamNetworkListenSocketDirectUDP()
{

	if ( m_pSock )
	{
		delete m_pSock;
		m_pSock = nullptr;
	}
}
