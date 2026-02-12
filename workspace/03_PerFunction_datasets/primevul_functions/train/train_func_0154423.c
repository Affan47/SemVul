ZrtpPacketDHPart* ZRtp::prepareDHPart1(ZrtpPacketCommit *commit, uint32_t* errMsg) {

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


    AlgorithmEnum* cp = &zrtpSymCiphers.getByName((const char*)commit->getCipherType());
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


        computeSharedSecretSet(zidRec);
    }

    cp = &zrtpPubKeys.getByName((const char*)commit->getPubKeysType());
    if (!cp->isValid()) {
        *errMsg = UnsuppPKExchange;
        return NULL;
    }
    if (*(int32_t*)(cp->getName()) == *(int32_t*)ec38) {
        if (*(int32_t*)(hash->getName()) != *(int32_t*)s384) {
            *errMsg = UnsuppHashType;
            return NULL;
        }
    }
    pubKey = cp;


    cp = &zrtpSasTypes.getByName((const char*)commit->getSasType());
    if (!cp->isValid()) {
        *errMsg = UnsuppSASScheme;
        return NULL;
    }
    sasType = cp;


    if (*(int32_t*)(dhContext->getDHtype()) != *(int32_t*)(pubKey->getName())) {
        delete dhContext;
        dhContext = new ZrtpDH(pubKey->getName());
        dhContext->generatePublicKey();
    }
    sendInfo(Info, InfoDH1DHGenerated);

    dhContext->getPubKeyBytes(pubKeyBytes);


    zrtpDH1.setPubKeyType(pubKey->getName());
    zrtpDH1.setMessageType((uint8_t*)DHPart1Msg);
    zrtpDH1.setRs1Id(rs1IDr);
    zrtpDH1.setRs2Id(rs2IDr);
    zrtpDH1.setAuxSecretId(auxSecretIDr);
    zrtpDH1.setPbxSecretId(pbxSecretIDr);
    zrtpDH1.setPv(pubKeyBytes);
    zrtpDH1.setH1(H1);

    int32_t len = zrtpDH1.getLength() * ZRTP_WORD_SIZE;


    uint8_t hmac[IMPL_MAX_DIGEST_LENGTH];
    uint32_t macLen;
    hmacFunctionImpl(H0, HASH_IMAGE_SIZE, (uint8_t*)zrtpDH1.getHeaderBase(), len-(HMAC_SIZE), hmac, &macLen);
    zrtpDH1.setHMAC(hmac);


    myRole = Responder;
    memcpy(peerHvi, commit->getHvi(), HVI_SIZE);


    if (msgShaContext != NULL) {
        closeHashCtx(msgShaContext, NULL);
    }
    msgShaContext = createHashCtx();


    hashCtxFunction(msgShaContext, (unsigned char*)currentHelloPacket->getHeaderBase(), currentHelloPacket->getLength() * ZRTP_WORD_SIZE);
    hashCtxFunction(msgShaContext, (unsigned char*)commit->getHeaderBase(), commit->getLength() * ZRTP_WORD_SIZE);
    hashCtxFunction(msgShaContext, (unsigned char*)zrtpDH1.getHeaderBase(), zrtpDH1.getLength() * ZRTP_WORD_SIZE);


    storeMsgTemp(commit);

    return &zrtpDH1;
}
