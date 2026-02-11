GetNextPacket(ECUpdateMsgSource *msg_source_array[])
{
	CECPacket *packet = 0;


	for(int i = 0; i < EC_STATUS_LAST_PRIO; i++) {
		if ( (packet = msg_source_array[i]->GetNextPacket()) != 0 ) {
			break;
		}
	}
	return packet;
}
