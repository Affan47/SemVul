OnPingServersReplyFromClientToCoordinator(Packet *packet)
{
	RakNet::BitStream incomingBs(packet->data, packet->length, false);
	incomingBs.IgnoreBytes(2);
	unsigned short serversToPingSize;
	SystemAddress serverAddress;
	SenderAndTargetAddress sata;
	incomingBs.Read(sata.senderClientAddress);
	incomingBs.Read(sata.targetClientAddress);
	bool objectExists;
	unsigned int index = forwardingRequestList.GetIndexFromKey(sata, &objectExists);
	if (objectExists==false)
		return;
	unsigned short idx;
	ServerWithPing swp;
	ForwardingRequest *fw = forwardingRequestList[index];
	if (fw->timeRequestedPings==0)
		return;

	incomingBs.Read(serversToPingSize);
	if (packet->systemAddress==sata.senderClientAddress)
	{
		for (idx=0; idx < serversToPingSize; idx++)
		{
			incomingBs.Read(swp.serverAddress);
			incomingBs.Read(swp.ping);
			unsigned int index2;
			for (index2=0; index2 < fw->sourceServerPings.Size(); index2++)
			{
				if (fw->sourceServerPings[index2].ping >= swp.ping )
					break;
			}
			fw->sourceServerPings.Insert(swp, index2, _FILE_AND_LINE_);
		}
	}
	else
	{
		for (idx=0; idx < serversToPingSize; idx++)
		{
			incomingBs.Read(swp.serverAddress);
			incomingBs.Read(swp.ping);

			unsigned int index2;
			for (index2=0; index2 < fw->targetServerPings.Size(); index2++)
			{
				if (fw->targetServerPings[index2].ping >= swp.ping )
					break;
			}
			fw->sourceServerPings.Insert(swp, index2, _FILE_AND_LINE_);
		}
	}


	if (fw->sourceServerPings.Size()>0 &&
		fw->targetServerPings.Size()>0)
	{
		fw->OrderRemainingServersToTry();
		fw->timeRequestedPings=0;
		TryNextServer(fw->sata, fw);
	}
}
