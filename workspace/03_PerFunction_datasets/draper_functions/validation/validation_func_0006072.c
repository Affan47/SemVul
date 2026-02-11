PushToUser(MessageID messageId, RakNet::RakString password, RakNet::AddressOrGUID remoteSystem)
{
	RakNet::BitStream output;
	output.Write(messageId);
	if (password.IsEmpty()==false)
		output.Write(password);
	Packet *p = AllocatePacketUnified(output.GetNumberOfBytesUsed());
	p->systemAddress=remoteSystem.systemAddress;
	p->systemAddress.systemIndex=(SystemIndex)-1;
	p->guid=remoteSystem.rakNetGuid;
	p->wasGeneratedLocally=true;
	memcpy(p->data, output.GetData(), output.GetNumberOfBytesUsed());
	rakPeerInterface->PushBackPacket(p, true);
}
