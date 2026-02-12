void ZrtpStateClass::evInitial(void) {
    DEBUGOUT((cout << "Checking for match in Initial.\n"));

    if (event->type == ZrtpInitial) {
        ZrtpPacketHello* hello = parent->prepareHello();
        sentVersion = hello->getVersionInt();


        sentPacket = static_cast<ZrtpPacketBase *>(hello);

        if (!parent->sendPacketZRTP(sentPacket)) {
            sendFailed();
            return;
        }
        if (startTimer(&T1) <= 0) {
            timerFailed(SevereNoTimer);
            return;
        }
        nextState(Detect);
    }
}
