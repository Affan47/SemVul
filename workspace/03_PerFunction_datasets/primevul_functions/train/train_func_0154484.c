void ZrtpStateClass::evCommitSent(void) {

    DEBUGOUT((cout << "Checking for match in CommitSend.\n"));

    char *msg, first, middle, last, secondLast;
    uint8_t *pkt;
    uint32_t errorCode = 0;

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        middle = tolower(*(msg+4));
        last = tolower(*(msg+7));
        secondLast = tolower(*(msg+6));


        if (first == 'h' && middle == 'o' && (last =='k' || last == ' ')) {
            return;
        }


        if (first == 'c' && last == ' ') {
            ZrtpPacketCommit zpCo(pkt);

            if (!parent->verifyH2(&zpCo)) {
                return;
            }
            cancelTimer();


            if (parent->compareCommit(&zpCo) < 0) {
                if (!multiStream) {
                    ZrtpPacketDHPart* dhPart1 = parent->prepareDHPart1(&zpCo, &errorCode);


                    if (dhPart1 == NULL) {
                        if (errorCode != IgnorePacket) {
                            sendErrorPacket(errorCode);
                        }
                        return;
                    }
                    nextState(WaitDHPart2);
                    sentPacket = static_cast<ZrtpPacketBase *>(dhPart1);
                }
                else {
                    ZrtpPacketConfirm* confirm = parent->prepareConfirm1MultiStream(&zpCo, &errorCode);


                    if (confirm == NULL) {
                        if (errorCode != IgnorePacket) {
                            sendErrorPacket(errorCode);
                        }
                        return;
                    }
                    nextState(WaitConfirm2);
                    sentPacket = static_cast<ZrtpPacketBase *>(confirm);
                }
                if (!parent->sendPacketZRTP(sentPacket)) {
                    sendFailed();
                }
            }


            else {
                if (startTimer(&T2) <= 0) {
                    timerFailed(SevereNoTimer);
                }
            }
            return;
        }


        if (first == 'd' && secondLast == '1') {
            cancelTimer();
            sentPacket = NULL;
            ZrtpPacketDHPart dpkt(pkt);
            ZrtpPacketDHPart* dhPart2 = parent->prepareDHPart2(&dpkt, &errorCode);


            if (dhPart2 == NULL) {
                if (errorCode != IgnorePacket) {
                    sendErrorPacket(errorCode);
                }
                else {
                    if (startTimer(&T2) <= 0) {
                        timerFailed(SevereNoTimer);
                    }
                }

                return;
            }
            sentPacket = static_cast<ZrtpPacketBase *>(dhPart2);
            nextState(WaitConfirm1);

            if (!parent->sendPacketZRTP(sentPacket)) {
                sendFailed();
                return;
            }
            if (startTimer(&T2) <= 0) {
                timerFailed(SevereNoTimer);
            }
            return;
        }


        if (multiStream && (first == 'c' && last == '1')) {
            cancelTimer();
            ZrtpPacketConfirm cpkt(pkt);

            ZrtpPacketConfirm* confirm = parent->prepareConfirm2MultiStream(&cpkt, &errorCode);


            if (confirm == NULL) {
                sendErrorPacket(errorCode);
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
                return;
            }


            if (!parent->srtpSecretsReady(ForReceiver)) {
                parent->sendInfo(Severe, CriticalSWError);
                sendErrorPacket(CriticalSWError);
                return;
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
