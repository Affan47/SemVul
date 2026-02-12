ZrtpPacketPingAck* ZRtp::preparePingAck(ZrtpPacketPing* ppkt) {
    if (ppkt->getLength() != 6)
        return NULL;


    zrtpPingAck.setLocalEpHash(ownZid);
    zrtpPingAck.setRemoteEpHash(ppkt->getEpHash());
    zrtpPingAck.setSSRC(peerSSRC);
    return &zrtpPingAck;
}
