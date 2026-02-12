void Server::handleCommand_DeletedBlocks(NetworkPacket* pkt)
{
	if (pkt->getSize() < 1)
		return;


	u8 count;
	*pkt >> count;

	RemoteClient *client = getClient(pkt->getPeerId());

	if ((s16)pkt->getSize() < 1 + (int)count * 6) {
		throw con::InvalidIncomingDataException
				("DELETEDBLOCKS length is too short");
	}

	for (u16 i = 0; i < count; i++) {
		v3s16 p;
		*pkt >> p;
		client->SetBlockNotSent(p);
	}
}
