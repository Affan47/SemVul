bool ZRtp::checkMultiStream(ZrtpPacketHello *hello) {

    int  i;
    int num = hello->getNumPubKeys();


    if (num == 0) {
        return true;
    }
    for (i = 0; i < num; i++) {
        if (*(int32_t*)(hello->getPubKeyType(i)) == *(int32_t*)mult) {
            return true;
        }
    }
    return false;
}
