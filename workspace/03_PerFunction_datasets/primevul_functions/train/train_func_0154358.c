bool ZrtpStateClass::subEvWaitRelayAck() {
    char *msg, first, last;
    uint8_t* pkt;


    if  (event->type == ZrtpPacket) {
        pkt = event->packet;
        msg = (char *)pkt + 4;

        first = tolower(*msg);
        last = tolower(*(msg+7));


        if (first == 'r' && last =='k') {
            cancelTimer();
            secSubstate = Normal;
            sentPacket = NULL;
        }
        return true;
    }

    else if (event->type == Timer) {
        if (!parent->sendPacketZRTP(sentPacket)) {
            sendFailed();
            return false;
        }
        if (nextTimer(&T2) <= 0) {


            return false;
        }
        return true;
    }
    return false;
}
