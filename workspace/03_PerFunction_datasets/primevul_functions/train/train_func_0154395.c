ZrtpPacketCommit* ZRtp::prepareCommit(ZrtpPacketHello *hello, uint32_t* errMsg) {


    peerClientId.assign((char*)hello->getClientId(), ZRTP_WORD_SIZE * 4);
    memcpy(peerHelloVersion, hello->getVersion(), ZRTP_WORD_SIZE);
    peerHelloVersion[ZRTP_WORD_SIZE] = 0;


    memcpy(peerZid, hello->getZid(), ZID_SIZE);
    if (memcmp(peerZid, ownZid, ZID_SIZE) == 0) {
        *errMsg = EqualZIDHello;
        return NULL;
    }
    memcpy(peerH3, hello->getH3(), HASH_IMAGE_SIZE);

    int32_t helloLen = hello->getLength() * ZRTP_WORD_SIZE;


    hashFunctionImpl((unsigned char*)hello->getHeaderBase(), helloLen, peerHelloHash);

    sendInfo(Info, InfoHelloReceived);


    sasType = findBestSASType(hello);

    if (!multiStream) {
        pubKey = findBestPubkey(hello);
        if (hash == NULL) {
            *errMsg = UnsuppHashType;
            return NULL;
        }
        if (cipher == NULL)
            cipher = findBestCipher(hello, pubKey);
        authLength = findBestAuthLen(hello);
        multiStreamAvailable = checkMultiStream(hello);
    }
    else {
        if (checkMultiStream(hello)) {
            return prepareCommitMultiStream(hello);
        }
        else {


            *errMsg = UnsuppPKExchange;
            return NULL;
        }
    }
    setNegotiatedHash(hash);


    dhContext = new ZrtpDH(pubKey->getName());
    dhContext->generatePublicKey();

    dhContext->getPubKeyBytes(pubKeyBytes);
    sendInfo(Info, InfoCommitDHGenerated);


    randomZRTP(randomIV, sizeof(randomIV));


    zidRec = getZidCacheInstance()->getRecord(peerZid);


    computeSharedSecretSet(zidRec);


    mitmSeen = hello->isMitmMode();

    signSasSeen = hello->isSasSign();


    zrtpDH2.setPubKeyType(pubKey->getName());
    zrtpDH2.setMessageType((uint8_t*)DHPart2Msg);
    zrtpDH2.setRs1Id(rs1IDi);
    zrtpDH2.setRs2Id(rs2IDi);
    zrtpDH2.setAuxSecretId(auxSecretIDi);
    zrtpDH2.setPbxSecretId(pbxSecretIDi);
    zrtpDH2.setPv(pubKeyBytes);
    zrtpDH2.setH1(H1);

    int32_t len = zrtpDH2.getLength() * ZRTP_WORD_SIZE;


    uint8_t hmac[IMPL_MAX_DIGEST_LENGTH];
    uint32_t macLen;
    hmacFunctionImpl(H0, HASH_IMAGE_SIZE, (uint8_t*)zrtpDH2.getHeaderBase(), len-(HMAC_SIZE), hmac, &macLen);
    zrtpDH2.setHMAC(hmac);


    computeHvi(&zrtpDH2, hello);

    zrtpCommit.setZid(ownZid);
    zrtpCommit.setHashType((uint8_t*)hash->getName());
    zrtpCommit.setCipherType((uint8_t*)cipher->getName());
    zrtpCommit.setAuthLen((uint8_t*)authLength->getName());
    zrtpCommit.setPubKeyType((uint8_t*)pubKey->getName());
    zrtpCommit.setSasType((uint8_t*)sasType->getName());
    zrtpCommit.setHvi(hvi);
    zrtpCommit.setH2(H2);

    len = zrtpCommit.getLength() * ZRTP_WORD_SIZE;


    hmacFunctionImpl(H1, HASH_IMAGE_SIZE, (uint8_t*)zrtpCommit.getHeaderBase(), len-(HMAC_SIZE), hmac, &macLen);
    zrtpCommit.setHMAC(hmac);


    msgShaContext = createHashCtx();
    hashCtxFunction(msgShaContext, (unsigned char*)hello->getHeaderBase(), helloLen);
    hashCtxFunction(msgShaContext, (unsigned char*)zrtpCommit.getHeaderBase(), len);


    storeMsgTemp(hello);

    return &zrtpCommit;
}
