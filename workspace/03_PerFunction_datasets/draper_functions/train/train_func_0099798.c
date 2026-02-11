SendChatRoomsList(RakNetGUID target)
{
	BitStream bsOut;
	bsOut.WriteCasted<MessageID>(ID_RELAY_PLUGIN);
	bsOut.WriteCasted<MessageID>(RPE_GET_GROUP_LIST_REPLY_FROM_SERVER);
	bsOut.WriteCasted<uint16_t>(chatRooms.Size());
	for (unsigned int i=0; i < chatRooms.Size(); i++)
	{
		bsOut.WriteCompressed(chatRooms[i]->roomName);
		bsOut.WriteCasted<uint16_t>(chatRooms[i]->usersInRoom.Size());
	}
	SendUnified(&bsOut, HIGH_PRIORITY, RELIABLE_ORDERED, 0, target, false);
}
