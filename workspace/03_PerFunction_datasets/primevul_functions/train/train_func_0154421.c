void ZrtpStateClass::evAckSent(void) {

    DEBUGOUT((cout << "Checking for match in AckSent.\n"));

    char *msg, first, last;
    uint8_t *pkt;
    uint32_t errorCode = 0;


    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));


        if (first == 'h' && last =='k') {
            cancelTimer();


            sentPacket = static_cast<ZrtpPacketBase *>(commitPkt);
            commitPkt = NULL;
            nextState(CommitSent);
            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();
                return;
            }
            if (startTimer(&T2) <= 0) {
                timerFailed(SevereNoTimer);
            }
            return;
        }


        if (first == 'h' && last ==' ') {
            ZrtpPacketHelloAck* helloAck = parent->prepareHelloAck();

            if (!parent->sendPacketZRTP(static_cast<ZrtpPacketBase *>(helloAck))) {
                nextState(Detect);
                parent->zrtpNegotiationFailed(Severe, SevereCannotSend);
            }
            return;
        }


        if (first == 'c' && last == ' ') {
            cancelTimer();
            ZrtpPacketCommit cpkt(pkt);

            if (!multiStream) {
                ZrtpPacketDHPart* dhPart1 = parent->prepareDHPart1(&cpkt, &errorCode);


                if (dhPart1 == NULL) {
                    if (errorCode != IgnorePacket) {
                        sendErrorPacket(errorCode);
                    }
                    return;
                }
                commitPkt = NULL;
                sentPacket = static_cast<ZrtpPacketBase *>(dhPart1);
                nextState(WaitDHPart2);
            }
            else {
                ZrtpPacketConfirm* confirm = parent->prepareConfirm1MultiStream(&cpkt, &errorCode);


                if (confirm == NULL) {
                    if (errorCode != IgnorePacket) {
                        sendErrorPacket(errorCode);
                    }
                    return;
                }
                sentPacket = static_cast<ZrtpPacketBase *>(confirm);
                nextState(WaitConfirm2);
            }
            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();
            }
        }
    }


    else if (event->type == Timer) {
        if (!parent->sendPacketZRTP(sentPacket)) {
            return sendFailed();
        }
        if (nextTimer(&T1) <= 0) {
            parent->zrtpNotSuppOther();
            commitPkt = NULL;


            nextState(Detect);
        }
    }
    else {
        if (event->type != ZrtpClose) {
            parent->zrtpNegotiationFailed(Severe, SevereProtocolError);
        }
        commitPkt = NULL;
        sentPacket = NULL;
        nextState(Initial);
    }
}
