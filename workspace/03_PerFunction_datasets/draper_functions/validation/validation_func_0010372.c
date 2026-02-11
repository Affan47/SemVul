SendOpen(uint16_t socket, Data &receive)
{

	Barry::Protocol::Packet packet;
	packet.socket = 0;
	packet.size = htobs(SB_SOCKET_PACKET_HEADER_SIZE);
	packet.command = SB_COMMAND_OPEN_SOCKET;
	packet.u.socket.socket = htobs(socket);
	packet.u.socket.sequence = m_zeroSocketSequence;

	Data send(&packet, SB_SOCKET_PACKET_HEADER_SIZE);
	try {
		RawSend(send);
		RawReceive(receive);
		if( Protocol::IsSequencePacket(receive) ) {
			m_modeSequencePacketSeen = true;


			RawReceive(receive);
		}
	} catch( Usb::Error & ) {
		eeout(send, receive);
		throw;
	}


}
