void ZRtp::setClientId(std::string id, HelloPacketVersion* hpv) {

    unsigned char tmp[CLIENT_ID_SIZE +1] = {' '};
    memcpy(tmp, id.c_str(), id.size());
    tmp[CLIENT_ID_SIZE] = 0;

    hpv->packet->setClientId(tmp);

    int32_t len = hpv->packet->getLength() * ZRTP_WORD_SIZE;


    uint8_t hmac[IMPL_MAX_DIGEST_LENGTH];
    uint32_t macLen;
    hmacFunctionImpl(H2, HASH_IMAGE_SIZE, (uint8_t*)hpv->packet->getHeaderBase(), len-(2*ZRTP_WORD_SIZE), hmac, &macLen);
    hpv->packet->setHMAC(hmac);


    hashFunctionImpl((uint8_t*)hpv->packet->getHeaderBase(), len, hpv->helloHash);
}
