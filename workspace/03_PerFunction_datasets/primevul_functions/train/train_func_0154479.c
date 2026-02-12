ZrtpQueue::rtpDataPacket(unsigned char* buffer, int32 rtn, InetHostAddress network_address, tpport_t transport_port)
{


    uint8 padSet = (*buffer & 0x20);
    if (padSet) {
        *buffer = *buffer & ~0x20;
    }

    IncomingRTPPkt* packet =
        new IncomingRTPPkt(buffer,rtn);


    if ( !packet->isHeaderValid() ) {
        delete packet;
        return 0;
    }


    CryptoContext* pcc = getInQueueCryptoContext(packet->getSSRC());


    if (pcc == NULL) {
        pcc = getInQueueCryptoContext(0);
        if (pcc != NULL) {
            pcc = pcc->newCryptoContextForSSRC(packet->getSSRC(), 0, 0L);
            if (pcc != NULL) {
                pcc->deriveSrtpKeys(0);
                setInQueueCryptoContext(pcc);
            }
        }
    }


    if (pcc != NULL) {
        int32 ret;
        if ((ret = packet->unprotect(pcc)) < 0) {
            if (!onSRTPPacketError(*packet, ret)) {
                delete packet;
                return 0;
            }
        }
        if (started && zrtpEngine->inState(WaitConfAck)) {
            zrtpEngine->conf2AckSecure();
        }
    }


    if (!onRTPPacketRecv(*packet) ) {
        delete packet;
        return 0;
    }
    if (padSet) {
        packet->reComputePayLength(true);
    }

    struct timeval recvtime;
    gettimeofday(&recvtime,NULL);

    bool source_created;
    SyncSourceLink* sourceLink =
            getSourceBySSRC(packet->getSSRC(),source_created);
    SyncSource* s = sourceLink->getSource();
    if ( source_created ) {

        setDataTransportPort(*s,transport_port);

        setNetworkAddress(*s,network_address);
        sourceLink->initStats();

        sourceLink->setInitialDataTime(recvtime);
        sourceLink->setProbation(getMinValidPacketSequence());
        if ( sourceLink->getHello() )
            onNewSyncSource(*s);
    }
    else if ( 0 == s->getDataTransportPort() ) {


        setDataTransportPort(*s,transport_port);
    }


    if (checkSSRCInIncomingRTPPkt(*sourceLink, source_created,
        network_address, transport_port) &&
        recordReception(*sourceLink,*packet,recvtime) ) {

        IncomingRTPPktLink* packetLink = new IncomingRTPPktLink(packet, sourceLink, recvtime,
                                       packet->getTimestamp() - sourceLink->getInitialDataTimestamp(),
                                       NULL,NULL,NULL,NULL);
        insertRecvPacket(packetLink);
    } else {


        delete packet;
        return 0;
    }


    if (!started && enableZrtp) {
        startZrtp();
    }
    return rtn;
}
