processIncomingStun(const QByteArray &buf, const QHostAddress &fromAddr, int fromPort, Datagram *dg)
	{
		QByteArray data;
		QHostAddress dataAddr;
		int dataPort;

		bool notStun;
		if(!pool->writeIncomingMessage(buf, &notStun, fromAddr, fromPort) && turn)
		{
			data = turn->processIncomingDatagram(buf, notStun, &dataAddr, &dataPort);
			if(!data.isNull())
			{
				dg->addr = dataAddr;
				dg->port = dataPort;
				dg->buf = data;
				return true;
			}
			else
			{
				if(debugLevel >= IceTransport::DL_Packet)
					emit q->debugLine("Warning: server responded with what doesn't seem to be a STUN or data packet, skipping.");
			}
		}

		return false;
	}
