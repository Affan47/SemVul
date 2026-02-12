ZrtpPacketConfirm* ZRtp::prepareConfirm1MultiStream(ZrtpPacketCommit* commit, uint32_t* errMsg) {

    sendInfo(Info, InfoRespCommitReceived);


    uint8_t tmpH3[IMPL_MAX_DIGEST_LENGTH];
    memcpy(peerH2, commit->getH2(), HASH_IMAGE_SIZE);
    hashFunctionImpl(peerH2, HASH_IMAGE_SIZE, tmpH3);

    if (memcmp(tmpH3, peerH3, HASH_IMAGE_SIZE) != 0) {
        *errMsg = IgnorePacket;
        return NULL;
    }


    if (!checkMsgHmac(peerH2)) {
        sendInfo(Severe, SevereHelloHMACFailed);
        *errMsg = CriticalSWError;
        return NULL;
    }


    AlgorithmEnum* cp = &zrtpPubKeys.getByName((const char*)commit->getPubKeysType());
    if (!cp->isValid() || *(int32_t*)(cp->getName()) != *(int32_t*)mult) {
        *errMsg = UnsuppPKExchange;
        return NULL;
    }


    cp = &zrtpSymCiphers.getByName((const char*)commit->getCipherType());
    if (!cp->isValid()) {
        *errMsg = UnsuppCiphertype;
        return NULL;
    }
    cipher = cp;


    cp = &zrtpAuthLengths.getByName((const char*)commit->getAuthLen());
    if (!cp->isValid()) {
        *errMsg = UnsuppSRTPAuthTag;
        return NULL;
    }
    authLength = cp;


    cp = &zrtpHashes.getByName((const char*)commit->getHashType());
    if (!cp->isValid()) {
        *errMsg = UnsuppHashType;
        return NULL;
    }


    if (*(int32_t*)(hash->getName()) != *(int32_t*)(cp->getName())) {
        hash = cp;
        setNegotiatedHash(hash);
    }
    myRole = Responder;


    if (msgShaContext != NULL) {
        closeHashCtx(msgShaContext, NULL);
    }
    msgShaContext = createHashCtx();


    hashCtxFunction(msgShaContext, (unsigned char*)currentHelloPacket->getHeaderBase(), currentHelloPacket->getLength() * ZRTP_WORD_SIZE);
    hashCtxFunction(msgShaContext, (unsigned char*)commit->getHeaderBase(), commit->getLength() * ZRTP_WORD_SIZE);

    closeHashCtx(msgShaContext, messageHash);
    msgShaContext = NULL;

    generateKeysMultiStream();


    zrtpConfirm1.setMessageType((uint8_t*)Confirm1Msg);
    zrtpConfirm1.setExpTime(0xFFFFFFFF);
    zrtpConfirm1.setIv(randomIV);
    zrtpConfirm1.setHashH0(H0);

    uint8_t confMac[MAX_DIGEST_LENGTH];
    uint32_t macLen;


    int32_t hmlen = (zrtpConfirm1.getLength() - 9) * ZRTP_WORD_SIZE;
    cipher->getEncrypt()(zrtpKeyR, cipher->getKeylen(), randomIV, zrtpConfirm1.getHashH0(), hmlen);


    hmacFunction(hmacKeyR, hashLength, (unsigned char*)zrtpConfirm1.getHashH0(), hmlen, confMac, &macLen);

    zrtpConfirm1.setHmac(confMac);


    storeMsgTemp(commit);
    return &zrtpConfirm1;
}
