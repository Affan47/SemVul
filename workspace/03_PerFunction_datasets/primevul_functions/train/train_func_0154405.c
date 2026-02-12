ZrtpPacketCommit* ZRtp::prepareCommitMultiStream(ZrtpPacketHello *hello) {

    randomZRTP(hvi, ZRTP_WORD_SIZE*4);

    zrtpCommit.setZid(ownZid);
    zrtpCommit.setHashType((uint8_t*)hash->getName());
    zrtpCommit.setCipherType((uint8_t*)cipher->getName());
    zrtpCommit.setAuthLen((uint8_t*)authLength->getName());
    zrtpCommit.setPubKeyType((uint8_t*)mult);
    zrtpCommit.setSasType((uint8_t*)sasType->getName());
    zrtpCommit.setNonce(hvi);
    zrtpCommit.setH2(H2);

    int32_t len = zrtpCommit.getLength() * ZRTP_WORD_SIZE;


    uint8_t hmac[IMPL_MAX_DIGEST_LENGTH];
    uint32_t macLen;
    hmacFunctionImpl(H1, HASH_IMAGE_SIZE, (uint8_t*)zrtpCommit.getHeaderBase(), len-(HMAC_SIZE), hmac, &macLen);
    zrtpCommit.setHMACMulti(hmac);


    msgShaContext = createHashCtx();

    int32_t helloLen = hello->getLength() * ZRTP_WORD_SIZE;
    hashCtxFunction(msgShaContext, (unsigned char*)hello->getHeaderBase(), helloLen);
    hashCtxFunction(msgShaContext, (unsigned char*)zrtpCommit.getHeaderBase(), len);


    storeMsgTemp(hello);

    return &zrtpCommit;
}
