void Server::handleCommand_Init2(NetworkPacket* pkt)
{
	session_t peer_id = pkt->getPeerId();
	verbosestream << "Server: Got TOSERVER_INIT2 from " << peer_id << std::endl;

	m_clients.event(peer_id, CSE_GotInit2);
	u16 protocol_version = m_clients.getProtocolVersion(peer_id);

	std::string lang;
	if (pkt->getSize() > 0)
		*pkt >> lang;


	infostream << "Server: Sending content to " << getPlayerName(peer_id) <<
		std::endl;


	SendItemDef(peer_id, m_itemdef, protocol_version);


	SendNodeDef(peer_id, m_nodedef, protocol_version);

	m_clients.event(peer_id, CSE_SetDefinitionsSent);


	sendMediaAnnouncement(peer_id, lang);

	RemoteClient *client = getClient(peer_id, CS_InitDone);


	client->setLangCode(lang);


	{
		PlayerSAO *sao = getPlayerSAO(peer_id);
		if (client && sao)
			SendActiveObjectRemoveAdd(client, sao);
	}


	sendDetachedInventories(peer_id, false);


	SendMovement(peer_id);


	u16 time = m_env->getTimeOfDay();
	float time_speed = g_settings->getFloat("time_speed");
	SendTimeOfDay(peer_id, time, time_speed);

	SendCSMRestrictionFlags(peer_id);


	if (client->net_proto_version < LATEST_PROTOCOL_VERSION) {
		SendChatMessage(peer_id, ChatMessage(CHATMESSAGE_TYPE_SYSTEM,
			L"# Server: WARNING: YOUR CLIENT'S VERSION MAY NOT BE FULLY COMPATIBLE "
			L"WITH THIS SERVER!"));
	}
}
