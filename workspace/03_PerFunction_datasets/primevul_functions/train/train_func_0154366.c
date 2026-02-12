void ZrtpStateClass::evWaitCommit(void) {

    DEBUGOUT((cout << "Checking for match in WaitCommit.\n"));

    char *msg, first, last;
    uint8_t *pkt;
    uint32_t errorCode = 0;

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));


        if (first == 'h' && last == ' ') {
            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();
            }
            return;
        }


        if (first == 'c' && last == ' ') {
            ZrtpPacketCommit cpkt(pkt);

            if (!multiStream) {
                ZrtpPacketDHPart* dhPart1 = parent->prepareDHPart1(&cpkt, &errorCode);


                if (dhPart1 == NULL) {
                    if (errorCode != IgnorePacket) {
                        sendErrorPacket(errorCode);
                    }
                    return;
                }
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
    else {
        if (event->type != ZrtpClose) {
            parent->zrtpNegotiationFailed(Severe, SevereProtocolError);
        }
        sentPacket = NULL;
        nextState(Initial);
    }
}
