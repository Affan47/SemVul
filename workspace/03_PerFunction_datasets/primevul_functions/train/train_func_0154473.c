ZrtpPacketDHPart* ZRtp::prepareDHPart2(ZrtpPacketDHPart *dhPart1, uint32_t* errMsg) {

    uint8_t* pvr;

    sendInfo(Info, InfoInitDH1Received);


    uint8_t tmpHash[IMPL_MAX_DIGEST_LENGTH];
    hashFunctionImpl(dhPart1->getH1(), HASH_IMAGE_SIZE, tmpHash);
    memcpy(peerH2, tmpHash, HASH_IMAGE_SIZE);
    hashFunctionImpl(peerH2, HASH_IMAGE_SIZE, tmpHash);

    if (memcmp(tmpHash, peerH3, HASH_IMAGE_SIZE) != 0) {
        *errMsg = IgnorePacket;
        return NULL;
    }


    if (!checkMsgHmac(peerH2)) {
        sendInfo(Severe, SevereHelloHMACFailed);
        *errMsg = CriticalSWError;
        return NULL;
    }


    DHss = new uint8_t[dhContext->getDhSize()];
    if (DHss == NULL) {
        *errMsg = CriticalSWError;
        return NULL;
    }


    pvr = dhPart1->getPv();
    if (!dhContext->checkPubKey(pvr)) {
        *errMsg = DHErrorWrongPV;
        return NULL;
    }
    dhContext->computeSecretKey(pvr, DHss);

    myRole = Initiator;


    hashCtxFunction(msgShaContext, (unsigned char*)dhPart1->getHeaderBase(), dhPart1->getLength() * ZRTP_WORD_SIZE);
    hashCtxFunction(msgShaContext, (unsigned char*)zrtpDH2.getHeaderBase(), zrtpDH2.getLength() * ZRTP_WORD_SIZE);


    closeHashCtx(msgShaContext, messageHash);
    msgShaContext = NULL;


    generateKeysInitiator(dhPart1, zidRec);

    delete dhContext;
    dhContext = NULL;


    storeMsgTemp(dhPart1);
    return &zrtpDH2;
}
