ConnectionState( eConnectionState state )
{
	int err = -1;

	CMessageConnectionState *Object = new CMessageConnectionState();

	if ( (state == estCONNECTED) ||
	     (state == estDISCONNECTED) )
	{

		m_sBuffer.Empty();
		m_bHandshake        = true;
		m_timeMyinfoTimeout = time(0);
		m_nNickListHandler  = 0;

		m_bExtProtocol = false;
		m_bGotIP       = false;

		m_UserList.Clear();

		m_bZMode = false;
		delete m_pZLib;
		m_pZLib = 0;
#if DCLIB_HAS_SSL == 1
		m_pMessageSSL.Init();
#endif

		if ( state == estCONNECTED )
		{
			UpdateReconnect( ersNONE );

			if ( m_bSSLMode && CConfig::Instance() )
			{
				if ( ChangeSocketMode( esmSSLCLIENT, CConfig::Instance()->GetTransferCert(), CConfig::Instance()->GetTransferKey() ) == false )
				{
					printf("change ssl mode failed\n");
				}
			}
		}
		else
		{
			if ( m_eReconnectState == ersFORCEMOVE )
			{
				UpdateReconnect( ersNONE );
			}
			else
			{
				UpdateReconnect( ersENABLED );
			}
		}
	}

	Object->m_eState   = state;
	Object->m_sMessage = GetSocketError();

	if ( m_pCallback != 0 )
	{
		err = m_pCallback->notify( this, Object );
	}
	else
	{
		err = DC_CallBack( Object );
	}


	if ( err == -1 )
	{
		delete Object;
	}


	if ( m_bHandleMyinfo && CConnectionManager::Instance() )
	{
		CConnectionManager::Instance()->SendMyInfoToConnectedServers();
	}
}
