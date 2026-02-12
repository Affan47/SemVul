void ZrtpStateClass::evDetect(void) {

    DEBUGOUT((cout << "Checking for match in Detect.\n"));

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
            sentPacket = NULL;
            nextState(AckDetected);
            return;
        }


        if (first == 'h' && last ==' ') {
            ZrtpPacketHello hpkt(pkt);

            cancelTimer();


            int32_t recvVersion = hpkt.getVersionInt();
            if (recvVersion > sentVersion) {
                if (startTimer(&T1) <= 0) {
                    timerFailed(SevereNoTimer);
                }
                return;
            }


            if (recvVersion != sentVersion) {
                ZRtp::HelloPacketVersion* hpv = parent->helloPackets;

                int32_t index;
                for (index = 0; hpv->packet && hpv->packet != parent->currentHelloPacket; hpv++, index++)
                    ;

                for(; index >= 0 && hpv->version > recvVersion; hpv--, index--)
                    ;

                if (index < 0) {
                    sendErrorPacket(UnsuppZRTPVersion);
                    return;
                }
                parent->currentHelloPacket = hpv->packet;
                sentVersion = parent->currentHelloPacket->getVersionInt();


                sentPacket = static_cast<ZrtpPacketBase *>(parent->currentHelloPacket);

                if (!parent->sendPacketZRTP(sentPacket)) {
                    sendFailed();
                    return;
                }
                if (startTimer(&T1) <= 0) {
                    timerFailed(SevereNoTimer);
                    return;
                }
                return;
            }
            ZrtpPacketHelloAck* helloAck = parent->prepareHelloAck();

            if (!parent->sendPacketZRTP(static_cast<ZrtpPacketBase *>(helloAck))) {
                parent->zrtpNegotiationFailed(Severe, SevereCannotSend);
                return;
            }


            commitPkt = parent->prepareCommit(&hpkt, &errorCode);

            nextState(AckSent);
            if (commitPkt == NULL) {
                sendErrorPacket(errorCode);
                return;
            }
            if (startTimer(&T1) <= 0) {
                timerFailed(SevereNoTimer);
            }
            T1.maxResend = 60;
        }
        return;
    }

    else if (event->type == Timer) {
        if (!parent->sendPacketZRTP(sentPacket)) {
            sendFailed();
            return;
        }
        if (nextTimer(&T1) <= 0) {
            commitPkt = NULL;
            parent->zrtpNotSuppOther();
            nextState(Detect);
        }
    }

    else if (event->type == ZrtpInitial) {
        cancelTimer();
        if (!parent->sendPacketZRTP(sentPacket)) {
            sendFailed();
            return;
        }
        if (startTimer(&T1) <= 0) {
            timerFailed(SevereNoTimer);
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
