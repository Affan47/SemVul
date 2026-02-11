HandleReceivedZeroPacket(Data &data)
{
	Protocol::CheckSize(data, SB_PACKET_HEADER_SIZE);
	MAKE_PACKETPTR_BUF(packet, data.GetData());

	if( packet->socket != 0 ) {
		UnregisterZeroSocketInterest();
		SetPendingError(_("RawChannel: Got packet not for socket-zero"));
	}

	switch( btohs(packet->command) )
	{
	case SB_COMMAND_CLOSE_SOCKET:
	case SB_COMMAND_REMOTE_CLOSE_SOCKET:


		UnregisterZeroSocketInterest();
		if( m_callback ) {
			m_callback->ChannelClose();
		}

		break;
	default:
		UnregisterZeroSocketInterest();
		if( m_callback ) {
			m_callback->ChannelError(_("RawChannel: Got unexpected socket zero packet"));
		}
		else {
			SetPendingError(_("RawChannel: Got unexpected socket zero packet"));
		}
		break;
	}

}
