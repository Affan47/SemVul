ZrtpPacketConfirm* ZRtp::prepareConfirm2MultiStream(ZrtpPacketConfirm* confirm1, uint32_t* errMsg) {


    sendInfo(Info, InfoInitConf1Received);

    uint8_t confMac[MAX_DIGEST_LENGTH];
    uint32_t macLen;

    closeHashCtx(msgShaContext, messageHash);
    msgShaContext = NULL;
    myRole = Initiator;

    generateKeysMultiStream();


    int32_t hmlen = (confirm1->getLength() - 9) * ZRTP_WORD_SIZE;


    hmacFunction(hmacKeyR, hashLength, (unsigned char*)confirm1->getHashH0(), hmlen, confMac, &macLen);

    if (memcmp(confMac, confirm1->getHmac(), HMAC_SIZE) != 0) {
        *errMsg = ConfirmHMACWrong;
        return NULL;
    }

    cipher->getDecrypt()(zrtpKeyR, cipher->getKeylen(), (uint8_t*)confirm1->getIv(), confirm1->getHashH0(), hmlen);


    uint8_t tmpHash[IMPL_MAX_DIGEST_LENGTH];
    hashFunctionImpl(confirm1->getHashH0(), HASH_IMAGE_SIZE, tmpHash);
    hashFunctionImpl(tmpHash, HASH_IMAGE_SIZE, tmpHash);
    memcpy(peerH2, tmpHash, HASH_IMAGE_SIZE);


    if (!checkMsgHmac(peerH2)) {
        sendInfo(Severe, SevereHelloHMACFailed);
        *errMsg = CriticalSWError;
        return NULL;
    }

    zrtpConfirm2.setMessageType((uint8_t*)Confirm2Msg);
    zrtpConfirm2.setHashH0(H0);
    zrtpConfirm2.setExpTime(0xFFFFFFFF);
    zrtpConfirm2.setIv(randomIV);


    hmlen = (zrtpConfirm2.getLength() - 9) * ZRTP_WORD_SIZE;
    cipher->getEncrypt()(zrtpKeyI, cipher->getKeylen(), randomIV, zrtpConfirm2.getHashH0(), hmlen);


    hmacFunction(hmacKeyI, hashLength, (unsigned char*)zrtpConfirm2.getHashH0(), hmlen, confMac, &macLen);

    zrtpConfirm2.setHmac(confMac);
    return &zrtpConfirm2;
}
