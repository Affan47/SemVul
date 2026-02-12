void ZrtpStateClass::evWaitConfirm1(void) {

    DEBUGOUT((cout << "Checking for match in WaitConfirm1.\n"));

    char *msg, first, last;
    uint8_t *pkt;
    uint32_t errorCode = 0;

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));


        if (first == 'c' && last == '1') {
            cancelTimer();
            ZrtpPacketConfirm cpkt(pkt);

            ZrtpPacketConfirm* confirm = parent->prepareConfirm2(&cpkt, &errorCode);


            if (confirm == NULL) {
                sendErrorPacket(errorCode);
                return;
            }


            if (!parent->srtpSecretsReady(ForReceiver)) {
                parent->sendInfo(Severe, CriticalSWError);
                sendErrorPacket(CriticalSWError);
                return;
            }
            nextState(WaitConfAck);
            sentPacket = static_cast<ZrtpPacketBase *>(confirm);

            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();
                return;
            }
            if (startTimer(&T2) <= 0) {
                timerFailed(SevereNoTimer);
            }
        }
    }
    else if (event->type == Timer) {
        if (!parent->sendPacketZRTP(sentPacket)) {
            sendFailed();
            return;
        }
        if (nextTimer(&T2) <= 0) {
            timerFailed(SevereTooMuchRetries);
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
