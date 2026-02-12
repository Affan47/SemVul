void CServer::GenerateServerInfo(CPacker *pPacker, int Token)
{

	int PlayerCount = 0, ClientCount = 0;
	for(int i = 0; i < MAX_CLIENTS; i++)
	{
		if(m_aClients[i].m_State != CClient::STATE_EMPTY)
		{
			if(GameServer()->IsClientPlayer(i))
				PlayerCount++;

			ClientCount++;
		}
	}

	if(Token != -1)
	{
		pPacker->Reset();
		pPacker->AddRaw(SERVERBROWSE_INFO, sizeof(SERVERBROWSE_INFO));
		pPacker->AddInt(Token);
	}

	pPacker->AddString(GameServer()->Version(), 32);
	pPacker->AddString(Config()->m_SvName, 64);
	pPacker->AddString(Config()->m_SvHostname, 128);
	pPacker->AddString(GetMapName(), 32);


	pPacker->AddString(GameServer()->GameType(), 16);


	int Flags = 0;
	if(Config()->m_Password[0])
		Flags |= SERVERINFO_FLAG_PASSWORD;
	if(GameServer()->TimeScore())
		Flags |= SERVERINFO_FLAG_TIMESCORE;
	pPacker->AddInt(Flags);

	pPacker->AddInt(Config()->m_SvSkillLevel);
	pPacker->AddInt(PlayerCount);
	pPacker->AddInt(Config()->m_SvPlayerSlots);
	pPacker->AddInt(ClientCount);
	pPacker->AddInt(max(ClientCount, Config()->m_SvMaxClients));

	if(Token != -1)
	{
		for(int i = 0; i < MAX_CLIENTS; i++)
		{
			if(m_aClients[i].m_State != CClient::STATE_EMPTY)
			{
				pPacker->AddString(ClientName(i), MAX_NAME_LENGTH);
				pPacker->AddString(ClientClan(i), MAX_CLAN_LENGTH);
				pPacker->AddInt(m_aClients[i].m_Country);
				pPacker->AddInt(m_aClients[i].m_Score);
				pPacker->AddInt(GameServer()->IsClientPlayer(i)?0:1);
			}
		}
	}
}
