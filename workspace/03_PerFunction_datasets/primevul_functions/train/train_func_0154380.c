void ZrtpStateClass::evSecureState(void) {

    DEBUGOUT((cout << "Checking for match in SecureState.\n"));

    char *msg, first, last;
    uint8_t *pkt;


    if (secSubstate == WaitSasRelayAck) {
        if (subEvWaitRelayAck())
            return;
    }

    if (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));


        if (first == 'c' && last == '2') {
            if (sentPacket != NULL && !parent->sendPacketZRTP(sentPacket)) {
                sentPacket = NULL;
                nextState(Initial);
                parent->srtpSecretsOff(ForSender);
                parent->srtpSecretsOff(ForReceiver);
                parent->zrtpNegotiationFailed(Severe, SevereCannotSend);
            }
            return;
        }


    }
    else if (event->type == Timer) {

        ;
    }

    else  {


        if (event->type == ErrorPkt)
            return;
        sentPacket = NULL;
        parent->srtpSecretsOff(ForSender);
        parent->srtpSecretsOff(ForReceiver);
        nextState(Initial);
        if (event->type != ZrtpClose) {
            parent->zrtpNegotiationFailed(Severe, SevereProtocolError);
        }
        parent->sendInfo(Info, InfoSecureStateOff);
    }
}
