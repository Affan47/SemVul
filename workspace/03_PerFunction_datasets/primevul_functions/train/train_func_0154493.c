void ZrtpStateClass::processEvent(Event_t *ev) {

    char *msg, first, middle, last;
    uint8_t *pkt;

    parent->synchEnter();

    event = ev;
    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;
        first = tolower(*msg);
        middle = tolower(*(msg+4));
        last = tolower(*(msg+7));


        if (!inState(WaitErrorAck)) {
            uint16_t totalLength = *(uint16_t*)(pkt+2);
            totalLength = zrtpNtohs(totalLength) * ZRTP_WORD_SIZE;
            totalLength += 12 + sizeof(uint32_t);

            if (totalLength != ev->length) {
                fprintf(stderr, "Total length does not match received length: %d - %ld\n", totalLength, ev->length);
                sendErrorPacket(MalformedPacket);
                parent->synchLeave();
                return;
            }
        }


        if (first == 'e' && middle =='r' && last == ' ') {


            cancelTimer();
            ZrtpPacketError epkt(pkt);
            ZrtpPacketErrorAck* eapkt = parent->prepareErrorAck(&epkt);
            parent->sendPacketZRTP(static_cast<ZrtpPacketBase *>(eapkt));
            event->type = ErrorPkt;
        }
        else if (first == 'p' && middle == ' ' && last == ' ') {
            ZrtpPacketPing ppkt(pkt);
            ZrtpPacketPingAck* ppktAck = parent->preparePingAck(&ppkt);
            if (ppktAck != NULL) {
                parent->sendPacketZRTP(static_cast<ZrtpPacketBase *>(ppktAck));
            }
            parent->synchLeave();
            return;
        }
        else if (first == 's' && last == 'y') {
            uint32_t errorCode = 0;
            ZrtpPacketSASrelay* srly = new ZrtpPacketSASrelay(pkt);
            ZrtpPacketRelayAck* rapkt = parent->prepareRelayAck(srly, &errorCode);
            parent->sendPacketZRTP(static_cast<ZrtpPacketBase *>(rapkt));
            parent->synchLeave();
            return;
        }
    }


    else if (event->type == ZrtpClose) {
        cancelTimer();
    }
    engine->processEvent(*this);
    parent->synchLeave();
}
