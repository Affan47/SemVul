void ZrtpStateClass::evAckDetected(void) {

    DEBUGOUT((cout << "Checking for match in AckDetected.\n"));

    char *msg, first, last;
    uint8_t *pkt;
    uint32_t errorCode = 0;

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));

#if 1


        if (first == 'h' && last ==' ') {


            ZrtpPacketHello hpkt(pkt);
            ZrtpPacketCommit* commit = parent->prepareCommit(&hpkt, &errorCode);


            if (commit == NULL) {
                sendErrorPacket(errorCode);
                return;
            }
            ZrtpPacketHelloAck *helloAck = parent->prepareHelloAck();
            nextState(WaitCommit);


            sentPacket = static_cast<ZrtpPacketBase *>(helloAck);
            if (!parent->sendPacketZRTP(static_cast<ZrtpPacketBase *>(helloAck))) {
                sendFailed();
            }
        }
#else


        if (first == 'h' && last == ' ') {

            ZrtpPacketHello hpkt(pkt);
            ZrtpPacketCommit* commit = parent->prepareCommit(&hpkt, &errorCode);

            if (commit == NULL) {
                sendErrorPacket(errorCode);
                return;
            }
            nextState(CommitSent);


            sentPacket = static_cast<ZrtpPacketBase *>(commit);
            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();
                return;
            }
            if (startTimer(&T2) <= 0) {
                timerFailed(SevereNoTimer);
            }
        }
#endif
    }
    else {
        if (event->type != ZrtpClose) {
            parent->zrtpNegotiationFailed(Severe, SevereProtocolError);
        }
        nextState(Initial);
    }
}
