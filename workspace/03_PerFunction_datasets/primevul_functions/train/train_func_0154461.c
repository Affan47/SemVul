ZrtpQueue::takeInDataPacket(void)
{
    InetHostAddress network_address;
    tpport_t transport_port;

    uint32 nextSize = (uint32)getNextDataPacketSize();
    unsigned char* buffer = new unsigned char[nextSize];
    int32 rtn = (int32)recvData(buffer, nextSize, network_address, transport_port);
    if ( (rtn < 0) || ((uint32)rtn > getMaxRecvPacketSize()) ){
        delete buffer;
        return 0;
    }

    IncomingZRTPPkt* packet = NULL;

    if ((*buffer & 0xf0) != 0x10) {
        return (rtpDataPacket(buffer, rtn, network_address, transport_port));
    }


    if (enableZrtp && zrtpEngine != NULL) {

        if (rtn < (12 + sizeof(HelloAckPacket_t)))
            return 0;


        uint16_t temp = rtn - CRC_SIZE;
        uint32_t crc = *(uint32_t*)(buffer + temp);
        crc = ntohl(crc);

        if (!zrtpCheckCksum(buffer, temp, crc)) {
            delete buffer;
            if (zrtpUserCallback != NULL)
                zrtpUserCallback->showMessage(Warning, WarningCRCmismatch);
            return 0;
        }

        packet = new IncomingZRTPPkt(buffer,rtn);

        uint32 magic = packet->getZrtpMagic();


        if (magic != ZRTP_MAGIC || zrtpEngine == NULL) {
            delete packet;
            return 0;
        }


        if (!started) {
            startZrtp();
         }


        unsigned char* extHeader =
                const_cast<unsigned char*>(packet->getHdrExtContent());
        extHeader -= 4;


        peerSSRC = packet->getSSRC();
        zrtpEngine->processZrtpMessage(extHeader, peerSSRC, rtn);
    }
    delete packet;
    return 0;
}
