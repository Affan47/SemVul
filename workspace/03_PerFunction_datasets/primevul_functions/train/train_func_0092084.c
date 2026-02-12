void CConnectionTransportUDPBase::RecvStats( const CMsgSteamSockets_UDP_Stats &msgStatsIn, SteamNetworkingMicroseconds usecNow )
{


	if ( msgStatsIn.has_stats() )
		m_connection.m_statsEndToEnd.ProcessMessage( msgStatsIn.stats(), usecNow );


	SpewVerbose( "[%s] Recv UDP stats:%s\n",
		ConnectionDescription(),
		DescribeStatsContents( msgStatsIn ).c_str()
	);


	if ( m_connection.BStateIsActive() )
	{


		if ( ( msgStatsIn.flags() & msgStatsIn.ACK_REQUEST_E2E ) || msgStatsIn.has_stats() )
		{
			bool bImmediate = ( msgStatsIn.flags() & msgStatsIn.ACK_REQUEST_IMMEDIATE ) != 0;
			m_connection.QueueEndToEndAck( bImmediate, usecNow );


			if ( bImmediate || m_connection.m_pTransport != this )
			{
				SendEndToEndStatsMsg( k_EStatsReplyRequest_NothingToSend, usecNow, "AckStats" );
			}
		}
	}
}
