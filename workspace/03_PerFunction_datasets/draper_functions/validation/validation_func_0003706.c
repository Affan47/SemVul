JoinGroup(RakNetGUID userGuid, RakString roomName)
{
	StrAndGuidAndRoom **strAndGuidSender = guidToStrHash.Peek(userGuid);
	if (strAndGuidSender)
	{
		if (roomName.IsEmpty())
			return 0;

		if ((*strAndGuidSender)->currentRoom==roomName)
			return 0;

		if ((*strAndGuidSender)->currentRoom.IsEmpty()==false)
			LeaveGroup(strAndGuidSender);

		RakString userName = (*strAndGuidSender)->str;

		for (unsigned int i=0; i < chatRooms.Size(); i++)
		{
			if (chatRooms[i]->roomName==roomName)
			{

				return JoinGroup(chatRooms[i],strAndGuidSender);
			}
		}


		RP_Group *room = RakNet::OP_NEW<RP_Group>(_FILE_AND_LINE_);
		room->roomName=roomName;
		chatRooms.Push(room, _FILE_AND_LINE_);
		return JoinGroup(room,strAndGuidSender);
	}

	return 0;
}
