SkipToVJCUserData(RakNet::BitStream *bsIn)
{
	bsIn->IgnoreBytes(sizeof(MessageID));
	unsigned short listSize;
	bsIn->Read(listSize);
	for (unsigned short i=0; i < listSize; i++)
	{
		bsIn->IgnoreBytes(RakNetGUID::size());
		bsIn->IgnoreBytes(SystemAddress::size());
		bsIn->IgnoreBytes(sizeof(unsigned char));
	}
}
