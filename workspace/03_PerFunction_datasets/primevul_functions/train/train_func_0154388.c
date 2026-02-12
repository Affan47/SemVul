int32_t ZrtpQueue::sendDataZRTP(const unsigned char *data, int32_t length) {

    OutgoingZRTPPkt* packet = new OutgoingZRTPPkt(data, length);

    packet->setSSRC(getLocalSSRC());

    packet->setSeqNum(senderZrtpSeqNo++);


    uint16_t temp = packet->getRawPacketSize() - CRC_SIZE;
    uint8_t* pt = (uint8_t*)packet->getRawPacket();
    uint32_t crc = zrtpGenerateCksum(pt, temp);

    crc = zrtpEndCksum(crc);


    pt += temp;
    *(uint32_t*)pt = htonl(crc);

    dispatchImmediate(packet);
    delete packet;

    return 1;
}
