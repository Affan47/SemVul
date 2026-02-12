void ZrtpStateClass::evWaitDHPart2(void) {

    DEBUGOUT((cout << "Checking for match in DHPart2.\n"));

    char *msg, first, secondLast, last;
    uint8_t *pkt;
    uint32_t errorCode = 0;

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));
        secondLast = tolower(*(msg+6));


        if (first == 'c' && last == ' ') {
            if (!parent->sendPacketZRTP(sentPacket)) {
                return sendFailed();
            }
            return;
        }


        if (first == 'd' && secondLast == '2') {
            ZrtpPacketDHPart dpkt(pkt);
            ZrtpPacketConfirm* confirm = parent->prepareConfirm1(&dpkt, &errorCode);

            if (confirm == NULL) {
                if (errorCode != IgnorePacket) {
                    sendErrorPacket(errorCode);
                }
                return;
            }
            nextState(WaitConfirm2);
            sentPacket = static_cast<ZrtpPacketBase *>(confirm);
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
