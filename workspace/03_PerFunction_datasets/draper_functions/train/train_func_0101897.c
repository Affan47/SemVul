Connect( CString hubname, CString server, CClient * client, bool sslconnect )
{
	if ( server.IsEmpty() )
	{
		return;
	}

	if ( hubname.IsEmpty() )
	{
		hubname = server;
	}

	if ( !client )
	{
		m_Mutex.Lock();

		client = (CClient*)GetHub(hubname,server);

		m_Mutex.UnLock();

		if ( client )
		{
			return;
		}

		client = new CClient();
	}

	client->SetHubName(hubname);

	AddHub(client);

	client->SetNick(CConfig::Instance()->GetNick( hubname, server ));
	client->SetConnectionType(CConfig::Instance()->GetSpeed());
	client->SetShareSize(CFileManager::Instance()->GetShareSize());
	client->SetMode(CConfig::Instance()->GetMode());
	client->SetAwayMode(CConfig::Instance()->GetAwayMode());

	client->SetComment(CConfig::Instance()->GetDescription(false, hubname, server));


	DCConfigHubProfile pConfigHubProfile;

	if ( CConfig::Instance()->GetBookmarkHubProfile( hubname, server, &pConfigHubProfile ) )
	{
		if ( pConfigHubProfile.m_bEMail )
			client->SetEMail(pConfigHubProfile.m_sEMail);
		else
			client->SetEMail(CConfig::Instance()->GetEMail());
		client->SetSSLMode(pConfigHubProfile.m_bSSL);
	}
	else
	{
		client->SetEMail(CConfig::Instance()->GetEMail());
		client->SetSSLMode(sslconnect);
	}

	client->Connect(server);
}
