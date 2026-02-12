ZrtpPacketConfirm* ZRtp::prepareConfirm1(ZrtpPacketDHPart* dhPart2, uint32_t* errMsg) {

    uint8_t* pvi;

    sendInfo(Info, InfoRespDH2Received);


    uint8_t tmpHash[IMPL_MAX_DIGEST_LENGTH];
    hashFunctionImpl(dhPart2->getH1(), HASH_IMAGE_SIZE, tmpHash);
    if (memcmp(tmpHash, peerH2, HASH_IMAGE_SIZE) != 0) {
        *errMsg = IgnorePacket;
        return NULL;
    }


    if (!checkMsgHmac(dhPart2->getH1())) {
        sendInfo(Severe, SevereCommitHMACFailed);
        *errMsg = CriticalSWError;
        return NULL;
    }


    computeHvi(dhPart2, currentHelloPacket);
    if (memcmp(hvi, peerHvi, HVI_SIZE) != 0) {
        *errMsg = DHErrorWrongHVI;
        return NULL;
    }
    DHss = new uint8_t[dhContext->getDhSize()];
    if (DHss == NULL) {
        *errMsg = CriticalSWError;
        return NULL;
    }

    pvi = dhPart2->getPv();
    if (!dhContext->checkPubKey(pvi)) {
        *errMsg = DHErrorWrongPV;
        return NULL;
    }
    dhContext->computeSecretKey(pvi, DHss);


    hashCtxFunction(msgShaContext, (unsigned char*)dhPart2->getHeaderBase(), dhPart2->getLength() * ZRTP_WORD_SIZE);

    closeHashCtx(msgShaContext, messageHash);
    msgShaContext = NULL;


    generateKeysResponder(dhPart2, zidRec);

    delete dhContext;
    dhContext = NULL;


    zrtpConfirm1.setMessageType((uint8_t*)Confirm1Msg);


    if (zidRec->isSasVerified() && !paranoidMode) {
        zrtpConfirm1.setSASFlag();
    }
    zrtpConfirm1.setExpTime(0xFFFFFFFF);
    zrtpConfirm1.setIv(randomIV);
    zrtpConfirm1.setHashH0(H0);


    if (enrollmentMode) {


        if (!peerIsEnrolled) {
            computePBXSecret();
            zidRec->setMiTMData(pbxSecretTmp);
        }

        zrtpConfirm1.setPBXEnrollment();
    }
    uint8_t confMac[MAX_DIGEST_LENGTH];
    uint32_t macLen;


    int hmlen = (zrtpConfirm1.getLength() - 9) * ZRTP_WORD_SIZE;
    cipher->getEncrypt()(zrtpKeyR, cipher->getKeylen(), randomIV, zrtpConfirm1.getHashH0(), hmlen);
    hmacFunction(hmacKeyR, hashLength, (unsigned char*)zrtpConfirm1.getHashH0(), hmlen, confMac, &macLen);

    zrtpConfirm1.setHmac(confMac);


    storeMsgTemp(dhPart2);
    return &zrtpConfirm1;
}
